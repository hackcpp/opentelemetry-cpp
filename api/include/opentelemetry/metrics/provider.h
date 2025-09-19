// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <mutex>

#include "opentelemetry/common/spin_lock_mutex.h"
#include "opentelemetry/metrics/meter_provider.h"

namespace opentelemetry {
namespace metrics
{

/**
 * Stores the singleton global MeterProvider.
 */
class Provider
{
public:
  /**
   * Returns the singleton MeterProvider.
   *
   * By default, a no-op MeterProvider is returned. This will never return a
   * nullptr MeterProvider.
   */
  static std::shared_ptr<MeterProvider> GetMeterProvider() noexcept
  {
    std::lock_guard<common::SpinLockMutex> guard(GetLock());
    return std::shared_ptr<MeterProvider>(GetProvider());
  }

  /**
   * Changes the singleton MeterProvider.
   */
  static void SetMeterProvider(const std::shared_ptr<MeterProvider> &tp) noexcept
  {
    std::lock_guard<common::SpinLockMutex> guard(GetLock());
    GetProvider() = tp;
  }

private:
 static std::shared_ptr<MeterProvider> &GetProvider() noexcept
  {
    static std::shared_ptr<MeterProvider> provider(nullptr);
    return provider;
  }

 static common::SpinLockMutex &GetLock() noexcept
  {
    static common::SpinLockMutex lock;
    return lock;
  }
};

}  // namespace metrics
}
