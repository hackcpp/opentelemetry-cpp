// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/sdk/metrics/metric_reader.h"
#include "opentelemetry/sdk/metrics/export/metric_producer.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

MetricReader::MetricReader() : metric_producer_(nullptr), shutdown_(false) {}

void MetricReader::SetMetricProducer(MetricProducer *metric_producer)
{
  metric_producer_ = metric_producer;
  OnInitialized();
}

bool MetricReader::Collect(std::function<bool(ResourceMetrics &metric_data)> callback) noexcept
{
  if (!metric_producer_)
  {
    return false;
  }

  auto result = metric_producer_->Produce();

  // According to the spec,
  //   When the Produce operation fails, the MetricProducer MAY return successfully collected
  //   results and a failed reasons list to the caller.
  // So we invoke the callback with whatever points we get back, even if the overall operation may
  // have failed.
  auto success = callback(result.points_);
  return (result.status_ == MetricProducer::Status::kSuccess) && success;
}

}  // namespace metrics
}  // namespace sdk
}
