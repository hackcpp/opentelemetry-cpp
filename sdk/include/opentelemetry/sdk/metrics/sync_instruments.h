// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/sdk/metrics/state/metric_storage.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

class LongHistogram : public opentelemetry::metrics::Histogram<std::uint64_t>
{
public:
  LongHistogram(const InstrumentDescriptor &instrument_descriptor,
                std::unique_ptr<SyncWritableMetricStorage> storage);

  void Record(uint64_t value,
              const opentelemetry::common::KeyValueIterable &attributes) noexcept override;

  void Record(uint64_t value) noexcept override;

private:
  InstrumentDescriptor instrument_descriptor_;
  std::unique_ptr<SyncWritableMetricStorage> storage_;
};

}
}
}