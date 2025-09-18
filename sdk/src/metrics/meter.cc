#include "opentelemetry/sdk/metrics/meter.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

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
    std::unique_ptr<opentelemetry::metrics::Histogram<uint64_t>> Meter::CreateUInt64Histogram(const std::string &name, const std::string &description, const std::string &unit) noexcept
    {
        InstrumentDescriptor instrument_descriptor = {std::string{name.data(), name.size()}, std::string{description.data(), description.size()},
                                                      std::string{unit.data(), unit.size()}, InstrumentType::kHistogram, InstrumentValueType::kLong};
        auto storage = RegisterSyncMetricStorage(instrument_descriptor);
        return std::unique_ptr<opentelemetry::metrics::Histogram<uint64_t>>{new LongHistogram(instrument_descriptor, std::move(storage))};
    }

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
            sync_storage = std::shared_ptr<SyncMetricStorage>(new SyncMetricStorage(instrument_descriptor, AggregationType::kHistogram));
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