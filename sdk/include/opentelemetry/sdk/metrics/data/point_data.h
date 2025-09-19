// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>

#include "opentelemetry/common/timestamp.h"
#include "opentelemetry/nostd/variant.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

using ValueType = opentelemetry::nostd::variant<int64_t, double>;

// TODO: remove ctors and initializers from below classes when GCC<5 stops
// shipping on Ubuntu

class SumPointData
{
public:
  // TODO: remove ctors and initializers when GCC<5 stops shipping on Ubuntu
  SumPointData(SumPointData &&)                      = default;
  SumPointData(const SumPointData &)                 = default;
  SumPointData &operator=(SumPointData &&)           = default;
  SumPointData()                                     = default;
  SumPointData &operator=(const SumPointData &other) = default;
  ~SumPointData()                                    = default;

  ValueType value_   = {};
  bool is_monotonic_ = true;
};

class LastValuePointData
{
public:
  // TODO: remove ctors and initializers when GCC<5 stops shipping on Ubuntu
  LastValuePointData(LastValuePointData &&)                      = default;
  LastValuePointData(const LastValuePointData &)                 = default;
  LastValuePointData &operator=(LastValuePointData &&)           = default;
  LastValuePointData()                                           = default;
  LastValuePointData &operator=(const LastValuePointData &other) = default;
  ~LastValuePointData()                                          = default;

  ValueType value_                                  = {};
  bool is_lastvalue_valid_                          = {};
  opentelemetry::common::SystemTimestamp sample_ts_ = {};
};

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

class DropPointData
{
public:
  // TODO: remove ctors and initializers when GCC<5 stops shipping on Ubuntu
  DropPointData(DropPointData &&)            = default;
  DropPointData(const DropPointData &)       = default;
  DropPointData()                            = default;
  DropPointData &operator=(DropPointData &&) = default;
};

}  // namespace metrics
}  // namespace sdk
}
