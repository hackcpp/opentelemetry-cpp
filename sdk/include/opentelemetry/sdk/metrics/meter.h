// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "opentelemetry/metrics/meter.h"
#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/sdk/metrics/meter_context.h"
#include "opentelemetry/sdk/instrumentationscope/instrumentation_scope.h"
#include "opentelemetry/sdk/metrics/data/metric_data.h"
#include "opentelemetry/sdk/metrics/state/metric_collector.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

class MetricStorage;
class SyncWritableMetricStorage;

class Meter: public opentelemetry::metrics::Meter
{
public:
  /** Construct a new Meter with the given  pipeline. */
  explicit Meter(
      std::weak_ptr<sdk::metrics::MeterContext> meter_context,
      std::unique_ptr<opentelemetry::sdk::instrumentationscope::InstrumentationScope> scope =
          opentelemetry::sdk::instrumentationscope::InstrumentationScope::Create("")) noexcept;

  std::unique_ptr<opentelemetry::metrics::Histogram<uint64_t>> CreateUInt64Histogram(const std::string &name, const std::string &description = "", const std::string &unit = "") noexcept override;

  const sdk::instrumentationscope::InstrumentationScope *GetInstrumentationScope() const noexcept {
    return scope_.get();
  }
  std::unique_ptr<SyncWritableMetricStorage> RegisterSyncMetricStorage(InstrumentDescriptor &instrument_descriptor);

    /** collect metrics across all the instruments configured for the meter **/
  std::vector<MetricData> Collect(CollectorHandle *collector,
                                  opentelemetry::common::SystemTimestamp collect_ts) noexcept;

private:
  std::unique_ptr<sdk::instrumentationscope::InstrumentationScope> scope_;
  std::weak_ptr<sdk::metrics::MeterContext> meter_context_;

  using MetricStorageMap = std::unordered_map<InstrumentDescriptor,
                                              std::shared_ptr<MetricStorage>,
                                              InstrumentDescriptorHash,
                                              InstrumentEqualNameCaseInsensitive>;
  MetricStorageMap storage_registry_;
  opentelemetry::common::SpinLockMutex storage_lock_;
};

}
}
}