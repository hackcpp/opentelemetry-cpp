// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/sdk/metrics/aggregation/aggregation.h"
// #include "opentelemetry/sdk/metrics/aggregation/base2_exponential_histogram_aggregation.h"
// #include "opentelemetry/sdk/metrics/aggregation/drop_aggregation.h"
#include "opentelemetry/sdk/metrics/aggregation/histogram_aggregation.h"
// #include "opentelemetry/sdk/metrics/aggregation/lastvalue_aggregation.h"
// #include "opentelemetry/sdk/metrics/aggregation/sum_aggregation.h"
// #include "opentelemetry/sdk/metrics/data/point_data.h"
#include "opentelemetry/sdk/metrics/instruments.h"
// #include "opentelemetry/version.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{
class AggregationConfig;

class DefaultAggregation
{
public:
  static std::unique_ptr<Aggregation> CreateAggregation(
      const opentelemetry::sdk::metrics::InstrumentDescriptor &instrument_descriptor,
      const AggregationConfig *aggregation_config)
  {
    bool is_monotonic = true;
    auto aggr_type    = GetDefaultAggregationType(instrument_descriptor.type_, is_monotonic);
    switch (aggr_type)
    {
      case AggregationType::kHistogram: {
        if (instrument_descriptor.value_type_ == InstrumentValueType::kLong)
        {
          return (std::unique_ptr<Aggregation>(new LongHistogramAggregation(aggregation_config)));
        }
        else
        {
          return nullptr;
        }

        break;
      }
      default:
        return nullptr;
    };
  }

  static std::unique_ptr<Aggregation> CreateAggregation(
      AggregationType aggregation_type,
      InstrumentDescriptor instrument_descriptor,
      const AggregationConfig *aggregation_config = nullptr)
  {
    switch (aggregation_type)
    {
      case AggregationType::kHistogram:
        if (instrument_descriptor.value_type_ == InstrumentValueType::kLong)
        {
          return std::unique_ptr<Aggregation>(new LongHistogramAggregation(aggregation_config));
        }
        else
        {
          return nullptr;
        }
        break;
      default:
        return nullptr;
    }
  }
 

  static AggregationType GetDefaultAggregationType(InstrumentType instrument_type,
                                                   bool &is_monotonic)
  {
    is_monotonic = false;
    switch (instrument_type)
    {
      case InstrumentType::kCounter:
      case InstrumentType::kObservableCounter:
        is_monotonic = true;
        return AggregationType::kSum;
      case InstrumentType::kUpDownCounter:
      case InstrumentType::kObservableUpDownCounter:
        return AggregationType::kSum;
      case InstrumentType::kHistogram:
        return AggregationType::kHistogram;
      case InstrumentType::kGauge:
      case InstrumentType::kObservableGauge:
        return AggregationType::kLastValue;
      default:
        return AggregationType::kDrop;
    }
  }

};

}  // namespace metrics
}  // namespace sdk
}
