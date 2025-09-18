// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>
#include <memory>

#include "opentelemetry/sdk/common/attribute_utils.h"
#include "opentelemetry/sdk/metrics/data/point_data.h"
#include "opentelemetry/sdk/metrics/instruments.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

using PointAttributes = opentelemetry::sdk::common::OrderedAttributeMap;
using PointType = HistogramPointData;

struct PointDataAttributes
{
  PointAttributes attributes;
  PointType point_data;
};

class MetricData
{
public:
  InstrumentDescriptor instrument_descriptor;
  AggregationTemporality aggregation_temporality;
  opentelemetry::common::SystemTimestamp start_ts;
  opentelemetry::common::SystemTimestamp end_ts;
  std::vector<PointDataAttributes> point_data_attr_;
};

}
}
}

