// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <mutex>
#include <functional>
#include "opentelemetry/common/spin_lock_mutex.h"
#include "opentelemetry/sdk/metrics/state/metric_storage.h"
#include "opentelemetry/sdk/metrics/aggregation/aggregation.h"
#include "opentelemetry/sdk/metrics/aggregation/default_aggregation.h"
#include "opentelemetry/sdk/metrics/state/temporal_metric_storage.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

class SyncMetricStorage : public MetricStorage, public SyncWritableMetricStorage
{
public:
  SyncMetricStorage(InstrumentDescriptor instrument_descriptor,
                    const AggregationType aggregation_type,
                    const AggregationConfig *aggregation_config = nullptr,
                    size_t attributes_limit = kAggregationCardinalityLimit)
      : instrument_descriptor_(instrument_descriptor),
        attributes_hashmap_(new AttributesHashMap(attributes_limit)),
        temporal_metric_storage_(instrument_descriptor, aggregation_type, aggregation_config)
  {
    create_default_aggregation_ = [&, aggregation_type,
                                   aggregation_config]() -> std::unique_ptr<Aggregation> {
      return DefaultAggregation::CreateAggregation(aggregation_type, instrument_descriptor_,
                                                   aggregation_config);
    };
  }

  void RecordLong(uint64_t value, const opentelemetry::common::KeyValueIterable &attributes) noexcept override
  {
    if (instrument_descriptor_.value_type_ != InstrumentValueType::kLong)
    {
      return;
    }

    std::lock_guard<opentelemetry::common::SpinLockMutex> guard(attribute_hashmap_lock_);
    attributes_hashmap_->GetOrSetDefault(attributes, nullptr, create_default_aggregation_)->Aggregate(value);
  }

  bool Collect(CollectorHandle *collector,
               const std::vector<std::shared_ptr<CollectorHandle>> &collectors,
               opentelemetry::common::SystemTimestamp sdk_start_ts,
               opentelemetry::common::SystemTimestamp collection_ts,
               std::function<bool(MetricData)> callback) noexcept override;

private:
  InstrumentDescriptor instrument_descriptor_;
  std::unique_ptr<AttributesHashMap> attributes_hashmap_;
  std::function<std::unique_ptr<Aggregation>()> create_default_aggregation_; 
  TemporalMetricStorage temporal_metric_storage_;
  opentelemetry::common::SpinLockMutex attribute_hashmap_lock_;
};


}
}
}