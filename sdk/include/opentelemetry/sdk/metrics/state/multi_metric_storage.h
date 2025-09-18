// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdint.h>
#include <memory>
#include <unordered_map>
#include <vector>

#include "opentelemetry/common/key_value_iterable.h"
#include "opentelemetry/common/timestamp.h"
#include "opentelemetry/sdk/metrics/state/attributes_hashmap.h"
#include "opentelemetry/sdk/metrics/state/metric_storage.h"
#include "opentelemetry/sdk/metrics/view/attributes_processor.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

class SyncMultiMetricStorage : public SyncWritableMetricStorage
{
public:
  void AddStorage(std::shared_ptr<SyncWritableMetricStorage> storage)
  {
    storages_.push_back(storage);
  }

  virtual void RecordLong(uint64_t value, const opentelemetry::common::KeyValueIterable &attributes) noexcept override
  {
      for (auto &s : storages_)
      {
          s->RecordLong(value, attributes);
      }
  }

private:
  std::vector<std::shared_ptr<SyncWritableMetricStorage>> storages_;
};

 
}  // namespace metrics
}  // namespace sdk
}
