// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include <functional>

#include "opentelemetry/common/timestamp.h"
#include "opentelemetry/sdk/metrics/data/metric_data.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/sdk/metrics/state/attributes_hashmap.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

class CollectorHandle;

class MetricStorage
{
public:
  MetricStorage()          = default;
  virtual ~MetricStorage() = default;

  /* collect the metrics from this storage */
  virtual bool Collect(CollectorHandle *collector,
                       const std::vector<std::shared_ptr<CollectorHandle>>& collectors,
                       opentelemetry::common::SystemTimestamp sdk_start_ts,
                       opentelemetry::common::SystemTimestamp collection_ts,
                       std::function<bool(MetricData)> callback) noexcept = 0;
};

/* Represents the sync metric storage */
class SyncWritableMetricStorage
{
public:
  virtual void RecordLong(uint64_t value, const opentelemetry::common::KeyValueIterable &attributes) noexcept = 0;

  virtual ~SyncWritableMetricStorage() = default;
};
}
}
}