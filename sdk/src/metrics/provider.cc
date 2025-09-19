// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/metrics/provider.h"
#include "opentelemetry/metrics/meter_provider.h"
#include "opentelemetry/sdk/metrics/provider.h"


namespace opentelemetry {
namespace sdk
{
namespace metrics
{

void Provider::SetMeterProvider(
    const std::shared_ptr<opentelemetry::metrics::MeterProvider> &mp) noexcept
{
   opentelemetry::metrics::Provider::SetMeterProvider(mp);
}

}  // namespace metrics
}  // namespace sdk
}
