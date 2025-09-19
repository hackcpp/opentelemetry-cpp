// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <mutex>

#include "opentelemetry/metrics/meter_provider.h"

namespace opentelemetry {
namespace sdk
{

namespace metrics
{

/**
 * Changes the singleton global MeterProvider.
 */
class Provider
{
public:
  /**
   * Changes the singleton MeterProvider.
   */
  static void SetMeterProvider(
      const std::shared_ptr<opentelemetry::metrics::MeterProvider> &mp) noexcept;
};

}  // namespace metrics
}  // namespace sdk
}
