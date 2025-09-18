// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/sdk/metrics/sync_instruments.h"
#include "opentelemetry/sdk/metrics/state/sync_metric_storage.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

LongHistogram::LongHistogram(const InstrumentDescriptor &instrument_descriptor,
                            std::unique_ptr<SyncWritableMetricStorage> storage)
    : instrument_descriptor_(instrument_descriptor),
      storage_(std::move(storage))
{
}

void LongHistogram::Record(uint64_t value,
                           const opentelemetry::common::KeyValueIterable &attributes) noexcept
{
  if (!storage_)
  {
    return;
  }
  return storage_->RecordLong(value, attributes);
}

void LongHistogram::Record(uint64_t value) noexcept
{
}

} // namespace metrics
} // namespace sdk
} // namespace opentelemetry