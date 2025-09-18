// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>

#include "opentelemetry/common/timestamp.h"
// #include "opentelemetry/nostd/variant.h"
// #include "opentelemetry/sdk/metrics/data/circular_buffer.h"
// #include "opentelemetry/version.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

using ValueType = uint64_t;

// TODO: remove ctors and initializers from below classes when GCC<5 stops
// shipping on Ubuntu

class HistogramPointData
{
public:
  // TODO: remove ctors and initializers when GCC<5 stops shipping on Ubuntu
  HistogramPointData(HistogramPointData &&)            = default;
  HistogramPointData &operator=(HistogramPointData &&) = default;
  HistogramPointData(const HistogramPointData &)       = default;
  HistogramPointData()                                 = default;
  HistogramPointData(const std::vector<double> &boundaries) : boundaries_(boundaries) {}
  HistogramPointData &operator=(const HistogramPointData &other) = default;
  ~HistogramPointData()                                          = default;

  std::vector<double> boundaries_ = {};
  ValueType sum_                  = {};
  ValueType min_                  = {};
  ValueType max_                  = {};
  std::vector<uint64_t> counts_   = {};
  uint64_t count_                 = {};
  bool record_min_max_            = true;
};

}  // namespace metrics
}  // namespace sdk
}
