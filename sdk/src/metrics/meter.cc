#include "opentelemetry/sdk/metrics/meter.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "opentelemetry/sdk/metrics/sync_instruments.h"
#include "opentelemetry/sdk/metrics/state/sync_metric_storage.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/sdk/metrics/state/multi_metric_storage.h"


namespace opentelemetry {
namespace sdk
{
namespace metrics
{
    Meter::Meter(
        std::weak_ptr<MeterContext> meter_context,
        std::unique_ptr<sdk::instrumentationscope::InstrumentationScope> instrumentation_scope) noexcept
        : scope_{std::move(instrumentation_scope)},
          meter_context_{std::move(meter_context)}
    {
    }

    std::unique_ptr<opentelemetry::metrics::Counter<uint64_t>> Meter::CreateUInt64Counter(
        const std::string& name,
        const std::string& description,
        const std::string& unit) noexcept
    {
    //   if (!meter_config_.IsEnabled())
    //   {
    //     return kNoopMeter.CreateUInt64Counter(name, description, unit);
    //   }

    //   if (!ValidateInstrument(name, description, unit))
    //   {
    //     OTEL_INTERNAL_LOG_ERROR("Meter::CreateUInt64Counter - failed. Invalid parameters."
    //                             << name << " " << description << " " << unit
    //                             << ". Measurements won't be recorded.");
    //     return opentelemetry::nostd::unique_ptr<metrics::Counter<uint64_t>>(
    //         new metrics::NoopCounter<uint64_t>(name, description, unit));
    //   }
      InstrumentDescriptor instrument_descriptor = {
          std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
          std::string{unit.data(), unit.size()}, InstrumentType::kCounter, InstrumentValueType::kLong};
      auto storage = RegisterSyncMetricStorage(instrument_descriptor);
      return std::unique_ptr<opentelemetry::metrics::Counter<uint64_t>>(
          new LongCounter(instrument_descriptor, std::move(storage)));
    }

   std::unique_ptr<opentelemetry::metrics::Counter<double>> Meter::CreateDoubleCounter(
    const std::string& name,
    const std::string& description,
    const std::string& unit) noexcept
    {
    //   if (!meter_config_.IsEnabled())
    //   {
    //     return kNoopMeter.CreateDoubleCounter(name, description, unit);
    //   }

    //   if (!ValidateInstrument(name, description, unit))
    //   {
    //     OTEL_INTERNAL_LOG_ERROR("Meter::CreateDoubleCounter - failed. Invalid parameters."
    //                             << name << " " << description << " " << unit
    //                             << ". Measurements won't be recorded.");
    //     return opentelemetry::nostd::unique_ptr<metrics::Counter<double>>(
    //         new metrics::NoopCounter<double>(name, description, unit));
    //   }
      InstrumentDescriptor instrument_descriptor = {
          std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
          std::string{unit.data(), unit.size()}, InstrumentType::kCounter,
          InstrumentValueType::kDouble};
      auto storage = RegisterSyncMetricStorage(instrument_descriptor);
      return std::unique_ptr<opentelemetry::metrics::Counter<double>>{
          new DoubleCounter(instrument_descriptor, std::move(storage))};
    }

// opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
// Meter::CreateInt64ObservableCounter(opentelemetry::nostd::string_view name,
//                                     opentelemetry::nostd::string_view description,
//                                     opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateInt64ObservableCounter(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateInt64ObservableCounter - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return GetNoopObservableInsrument();
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kObservableCounter,
//       InstrumentValueType::kLong};
//   auto storage = RegisterAsyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::shared_ptr<metrics::ObservableInstrument>{
//       new ObservableInstrument(instrument_descriptor, std::move(storage), observable_registry_)};
// }

// opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
// Meter::CreateDoubleObservableCounter(opentelemetry::nostd::string_view name,
//                                      opentelemetry::nostd::string_view description,
//                                      opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateDoubleObservableCounter(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateDoubleObservableCounter - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return GetNoopObservableInsrument();
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kObservableCounter,
//       InstrumentValueType::kDouble};
//   auto storage = RegisterAsyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::shared_ptr<metrics::ObservableInstrument>{
//       new ObservableInstrument(instrument_descriptor, std::move(storage), observable_registry_)};
// }

    std::unique_ptr<opentelemetry::metrics::Histogram<uint64_t>> Meter::CreateUInt64Histogram(
        const std::string &name,
        const std::string &description,
        const std::string &unit) noexcept
    {
        //   if (!meter_config_.IsEnabled())
        //   {
        //     return kNoopMeter.CreateUInt64Histogram(name, description, unit);
        //   }

        //   if (!ValidateInstrument(name, description, unit))
        //   {
        //     OTEL_INTERNAL_LOG_ERROR("Meter::CreateUInt64Histogram - failed. Invalid parameters."
        //                             << name << " " << description << " " << unit
        //                             << ". Measurements won't be recorded.");
        //     return opentelemetry::nostd::unique_ptr<metrics::Histogram<uint64_t>>(
        //         new metrics::NoopHistogram<uint64_t>(name, description, unit));
        //   }
        InstrumentDescriptor instrument_descriptor = {
            std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
            std::string{unit.data(), unit.size()}, InstrumentType::kHistogram,
            InstrumentValueType::kLong};
        auto storage = RegisterSyncMetricStorage(instrument_descriptor);
        return std::unique_ptr<opentelemetry::metrics::Histogram<uint64_t>>{
            new LongHistogram(instrument_descriptor, std::move(storage))};
    }

    std::unique_ptr<opentelemetry::metrics::Histogram<double>> Meter::CreateDoubleHistogram(
        const std::string &name,
        const std::string &description,
        const std::string &unit) noexcept
    {
        //   if (!meter_config_.IsEnabled())
        //   {
        //     return kNoopMeter.CreateDoubleHistogram(name, description, unit);
        //   }

        //   if (!ValidateInstrument(name, description, unit))
        //   {
        //     OTEL_INTERNAL_LOG_ERROR("Meter::CreateDoubleHistogram - failed. Invalid parameters."
        //                             << name << " " << description << " " << unit
        //                             << ". Measurements won't be recorded.");
        //     return opentelemetry::nostd::unique_ptr<metrics::Histogram<double>>(
        //         new metrics::NoopHistogram<double>(name, description, unit));
        //   }
        InstrumentDescriptor instrument_descriptor = {
            std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
            std::string{unit.data(), unit.size()}, InstrumentType::kHistogram,
            InstrumentValueType::kDouble};
        auto storage = RegisterSyncMetricStorage(instrument_descriptor);
        return std::unique_ptr<opentelemetry::metrics::Histogram<double>>{
            new DoubleHistogram(instrument_descriptor, std::move(storage))};
    }

// #if OPENTELEMETRY_ABI_VERSION_NO >= 2
// opentelemetry::nostd::unique_ptr<metrics::Gauge<int64_t>> Meter::CreateInt64Gauge(
//     opentelemetry::nostd::string_view name,
//     opentelemetry::nostd::string_view description,
//     opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateInt64Gauge(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateInt64Gauge - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return opentelemetry::nostd::unique_ptr<metrics::Gauge<int64_t>>(
//         new metrics::NoopGauge<int64_t>(name, description, unit));
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kGauge, InstrumentValueType::kLong};
//   auto storage = RegisterSyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::unique_ptr<metrics::Gauge<int64_t>>{
//       new LongGauge(instrument_descriptor, std::move(storage))};
// }

// opentelemetry::nostd::unique_ptr<metrics::Gauge<double>> Meter::CreateDoubleGauge(
//     opentelemetry::nostd::string_view name,
//     opentelemetry::nostd::string_view description,
//     opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateDoubleGauge(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateDoubleGauge - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return opentelemetry::nostd::unique_ptr<metrics::Gauge<double>>(
//         new metrics::NoopGauge<double>(name, description, unit));
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kGauge, InstrumentValueType::kDouble};
//   auto storage = RegisterSyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::unique_ptr<metrics::Gauge<double>>{
//       new DoubleGauge(instrument_descriptor, std::move(storage))};
// }
// #endif

// opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
// Meter::CreateInt64ObservableGauge(opentelemetry::nostd::string_view name,
//                                   opentelemetry::nostd::string_view description,
//                                   opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateInt64ObservableGauge(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateInt64ObservableGauge - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return GetNoopObservableInsrument();
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kObservableGauge,
//       InstrumentValueType::kLong};
//   auto storage = RegisterAsyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::shared_ptr<metrics::ObservableInstrument>{
//       new ObservableInstrument(instrument_descriptor, std::move(storage), observable_registry_)};
// }

// opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
// Meter::CreateDoubleObservableGauge(opentelemetry::nostd::string_view name,
//                                    opentelemetry::nostd::string_view description,
//                                    opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateDoubleObservableGauge(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateDoubleObservableGauge - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return GetNoopObservableInsrument();
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kObservableGauge,
//       InstrumentValueType::kDouble};
//   auto storage = RegisterAsyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::shared_ptr<metrics::ObservableInstrument>{
//       new ObservableInstrument(instrument_descriptor, std::move(storage), observable_registry_)};
// }

std::unique_ptr<opentelemetry::metrics::UpDownCounter<int64_t>> Meter::CreateInt64UpDownCounter(
    const std::string& name,
    const std::string& description,
    const std::string& unit) noexcept
{
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateInt64UpDownCounter(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateInt64UpDownCounter - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return opentelemetry::nostd::unique_ptr<metrics::UpDownCounter<int64_t>>(
//         new metrics::NoopUpDownCounter<int64_t>(name, description, unit));
//   }
  InstrumentDescriptor instrument_descriptor = {
      std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
      std::string{unit.data(), unit.size()}, InstrumentType::kUpDownCounter,
      InstrumentValueType::kLong};
  auto storage = RegisterSyncMetricStorage(instrument_descriptor);
  return std::unique_ptr<opentelemetry::metrics::UpDownCounter<int64_t>>{
      new LongUpDownCounter(instrument_descriptor, std::move(storage))};
}

std::unique_ptr<opentelemetry::metrics::UpDownCounter<double>> Meter::CreateDoubleUpDownCounter(
    const std::string& name,
    const std::string& description,
    const std::string& unit) noexcept
{
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateDoubleUpDownCounter(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR("Meter::CreateDoubleUpDownCounter - failed. Invalid parameters."
//                             << name << " " << description << " " << unit
//                             << ". Measurements won't be recorded.");
//     return opentelemetry::nostd::unique_ptr<metrics::UpDownCounter<double>>(
//         new metrics::NoopUpDownCounter<double>(name, description, unit));
//   }
  InstrumentDescriptor instrument_descriptor = {
      std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
      std::string{unit.data(), unit.size()}, InstrumentType::kUpDownCounter,
      InstrumentValueType::kDouble};
  auto storage = RegisterSyncMetricStorage(instrument_descriptor);
  return std::unique_ptr<opentelemetry::metrics::UpDownCounter<double>>{
      new DoubleUpDownCounter(instrument_descriptor, std::move(storage))};
}

// opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
// Meter::CreateInt64ObservableUpDownCounter(opentelemetry::nostd::string_view name,
//                                           opentelemetry::nostd::string_view description,
//                                           opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateInt64ObservableUpDownCounter(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR(
//         "Meter::CreateInt64ObservableUpDownCounter - failed. Invalid parameters -"
//         << name << " " << description << " " << unit << ". Measurements won't be recorded.");
//     return GetNoopObservableInsrument();
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kObservableUpDownCounter,
//       InstrumentValueType::kLong};
//   auto storage = RegisterAsyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::shared_ptr<metrics::ObservableInstrument>{
//       new ObservableInstrument(instrument_descriptor, std::move(storage), observable_registry_)};
// }

// opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
// Meter::CreateDoubleObservableUpDownCounter(opentelemetry::nostd::string_view name,
//                                            opentelemetry::nostd::string_view description,
//                                            opentelemetry::nostd::string_view unit) noexcept
// {
//   if (!meter_config_.IsEnabled())
//   {
//     return kNoopMeter.CreateDoubleObservableUpDownCounter(name, description, unit);
//   }

//   if (!ValidateInstrument(name, description, unit))
//   {
//     OTEL_INTERNAL_LOG_ERROR(
//         "Meter::CreateDoubleObservableUpDownCounter - failed. Invalid parameters."
//         << name << " " << description << " " << unit << ". Measurements won't be recorded.");
//     return GetNoopObservableInsrument();
//   }
//   InstrumentDescriptor instrument_descriptor = {
//       std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
//       std::string{unit.data(), unit.size()}, InstrumentType::kObservableUpDownCounter,
//       InstrumentValueType::kDouble};
//   auto storage = RegisterAsyncMetricStorage(instrument_descriptor);
//   return opentelemetry::nostd::shared_ptr<metrics::ObservableInstrument>{
//       new ObservableInstrument(instrument_descriptor, std::move(storage), observable_registry_)};
// }

    std::unique_ptr<SyncWritableMetricStorage> Meter::RegisterSyncMetricStorage(InstrumentDescriptor &instrument_descriptor)
    {
        std::lock_guard<opentelemetry::common::SpinLockMutex> guard(storage_lock_);
        auto ctx = meter_context_.lock();
        if (!ctx)
        {
            return nullptr;
        }

        std::unique_ptr<SyncWritableMetricStorage> storages(new SyncMultiMetricStorage());

        std::shared_ptr<SyncMetricStorage> sync_storage{};
        auto storage_iter = storage_registry_.find(instrument_descriptor);
        if (storage_iter != storage_registry_.end())
        {
            // static_pointer_cast is okay here. If storage_registry_.find is successful
            // InstrumentEqualNameCaseInsensitive ensures that the
            // instrument type and value type are the same for the existing and new instrument.
            sync_storage = std::static_pointer_cast<SyncMetricStorage>(storage_iter->second);
        }
        else
        {
            bool unused;
            auto aggregation_type = DefaultAggregation::GetDefaultAggregationType(instrument_descriptor.type_, unused);
            sync_storage = std::shared_ptr<SyncMetricStorage>(new SyncMetricStorage(instrument_descriptor, aggregation_type));
            storage_registry_.insert({instrument_descriptor, sync_storage});
        }
        auto sync_multi_storage = static_cast<SyncMultiMetricStorage *>(storages.get());
        sync_multi_storage->AddStorage(sync_storage);

        return storages;
    }

    std::vector<MetricData> Meter::Collect(CollectorHandle *collector,
                                           opentelemetry::common::SystemTimestamp collect_ts) noexcept
    {

        std::vector<MetricData> metric_data_list;
        auto ctx = meter_context_.lock();
        if (!ctx)
        {
            return std::vector<MetricData>{};
        }
        std::lock_guard<opentelemetry::common::SpinLockMutex> guard(storage_lock_);
        for (auto &metric_storage : storage_registry_)
        {
            metric_storage.second->Collect(collector, ctx->GetCollectors(), ctx->GetSDKStartTime(),
                                           collect_ts, [&metric_data_list](const MetricData &metric_data)
                                           {
                                     metric_data_list.push_back(metric_data);
                                     return true; });
        }
        return metric_data_list;
    }

}
}
}