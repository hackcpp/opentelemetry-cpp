// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>
#include <string>

namespace opentelemetry {
namespace metrics
{

class Meter;

/**
 * Creates new Meter instances.
 */
class MeterProvider
{
public:
  virtual ~MeterProvider() = default;

  /**
   * Gets or creates a named Meter instance (ABI)
   *
   * @since ABI_VERSION 1
   *
   * @param[in] name Meter instrumentation scope
   * @param[in] version Instrumentation scope version, optional
   * @param[in] schema_url Instrumentation scope schema URL, optional
   */
  virtual std::shared_ptr<Meter> GetMeter(const std::string &name,
                                          const std::string &version = "",
                                          const std::string &schema_url = "") noexcept = 0;
};
}  // namespace metrics
}
