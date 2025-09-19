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

    std::unique_ptr<opentelemetry::metrics::Counter<uint64_t>> CreateUInt64Counter(
      const std::string& name,
      const std::string& description = "",
      const std::string& unit        = "") noexcept override;

    std::unique_ptr<opentelemetry::metrics::Counter<double>> CreateDoubleCounter(
      const std::string& name,
      const std::string& description = "",
      const std::string& unit        = "") noexcept override;

  // nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument> CreateInt64ObservableCounter(
  //     nostd::string_view name,
  //     nostd::string_view description = "",
  //     nostd::string_view unit        = "") noexcept override;

  // nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument> CreateDoubleObservableCounter(
  //     nostd::string_view name,
  //     nostd::string_view description = "",
  //     nostd::string_view unit        = "") noexcept override;

   std::unique_ptr<opentelemetry::metrics::Histogram<uint64_t>> CreateUInt64Histogram(
      const std::string& name,
      const std::string& description = "",
      const std::string& unit        = "") noexcept override;

   std::unique_ptr<opentelemetry::metrics::Histogram<double>> CreateDoubleHistogram(
      const std::string& name,
      const std::string& description = "",
      const std::string& unit        = "") noexcept override;

// #if OPENTELEMETRY_ABI_VERSION_NO >= 2
//   nostd::unique_ptr<opentelemetry::metrics::Gauge<int64_t>> CreateInt64Gauge(
//       nostd::string_view name,
//       nostd::string_view description = "",
//       nostd::string_view unit        = "") noexcept override;

//   nostd::unique_ptr<opentelemetry::metrics::Gauge<double>> CreateDoubleGauge(
//       nostd::string_view name,
//       nostd::string_view description = "",
//       nostd::string_view unit        = "") noexcept override;
// #endif

  // nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument> CreateInt64ObservableGauge(
  //     nostd::string_view name,
  //     nostd::string_view description = "",
  //     nostd::string_view unit        = "") noexcept override;

  // nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument> CreateDoubleObservableGauge(
  //     nostd::string_view name,
  //     nostd::string_view description = "",
  //     nostd::string_view unit        = "") noexcept override;

  std::unique_ptr<opentelemetry::metrics::UpDownCounter<int64_t>> CreateInt64UpDownCounter(
      const std::string& name,
      const std::string& description = "",
      const std::string& unit        = "") noexcept override;

  std::unique_ptr<opentelemetry::metrics::UpDownCounter<double>> CreateDoubleUpDownCounter(
      const std::string& name,
      const std::string& description = "",
      const std::string& unit        = "") noexcept override;

  // nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
  // CreateInt64ObservableUpDownCounter(nostd::string_view name,
  //                                    nostd::string_view description = "",
  //                                    nostd::string_view unit        = "") noexcept override;

  // nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
  // CreateDoubleObservableUpDownCounter(nostd::string_view name,
  //                                     nostd::string_view description = "",
  //                                     nostd::string_view unit        = "") noexcept override;

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