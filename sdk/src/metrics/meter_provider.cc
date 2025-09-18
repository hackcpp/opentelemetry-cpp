// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include <chrono>
#include <mutex>
#include <utility>

#include "opentelemetry/common/key_value_iterable.h"
#include "opentelemetry/metrics/meter.h"
// #include "opentelemetry/sdk/instrumentationscope/instrumentation_scope.h"
// #include "opentelemetry/sdk/instrumentationscope/scope_configurator.h"
// #include "opentelemetry/sdk/metrics/export/metric_filter.h"
#include "opentelemetry/sdk/metrics/meter.h"
// #include "opentelemetry/sdk/metrics/meter_config.h"
// #include "opentelemetry/sdk/metrics/meter_context.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
// #include "opentelemetry/sdk/metrics/metric_reader.h"
// #include "opentelemetry/sdk/metrics/view/instrument_selector.h"
// #include "opentelemetry/sdk/metrics/view/meter_selector.h"
// #include "opentelemetry/sdk/metrics/view/view.h"
// #include "opentelemetry/sdk/metrics/view/view_registry.h"
#include "opentelemetry/sdk/resource/resource.h"
// #include "opentelemetry/version.h"


namespace opentelemetry {
namespace sdk
{
namespace metrics
{
namespace resource    = opentelemetry::sdk::resource;
namespace metrics_api = opentelemetry::metrics;

MeterProvider::MeterProvider(std::unique_ptr<MeterContext> context) noexcept
    : context_(std::move(context))
{}

std::shared_ptr<metrics_api::Meter> MeterProvider::GetMeter(
    const std::string& name,
    const std::string& version,
    const std::string& schema_url) noexcept
{
  const opentelemetry::common::KeyValueIterable *attributes = nullptr;

  const std::lock_guard<std::mutex> guard(lock_);

  for (auto &meter : context_->GetMeters())
  {
    auto meter_lib = meter->GetInstrumentationScope();
    if (meter_lib->equal(name, version, schema_url, attributes))
    {
      return std::shared_ptr<metrics_api::Meter>{meter};
    }
  }

  instrumentationscope::InstrumentationScopeAttributes attrs_map(attributes);
  auto scope =
      instrumentationscope::InstrumentationScope::Create(name, version, schema_url, attrs_map);

  auto meter = std::shared_ptr<Meter>(new Meter(context_, std::move(scope)));
  context_->AddMeter(meter);
  return std::shared_ptr<metrics_api::Meter>{meter};
}

const resource::Resource &MeterProvider::GetResource() const noexcept
{
  return context_->GetResource();
}

// void MeterProvider::AddMetricReader(std::shared_ptr<MetricReader> reader,
//                                     std::unique_ptr<MetricFilter> metric_filter) noexcept
// {
//   context_->AddMetricReader(std::move(reader), std::move(metric_filter));
// }

// void MeterProvider::AddView(std::unique_ptr<InstrumentSelector> instrument_selector,
//                             std::unique_ptr<MeterSelector> meter_selector,
//                             std::unique_ptr<View> view) noexcept
// {
//   context_->AddView(std::move(instrument_selector), std::move(meter_selector), std::move(view));
// }

// #ifdef ENABLE_METRICS_EXEMPLAR_PREVIEW

// void MeterProvider::SetExemplarFilter(metrics::ExemplarFilterType exemplar_filter_type) noexcept
// {
//   context_->SetExemplarFilter(exemplar_filter_type);
// }

// #endif  // ENABLE_METRICS_EXEMPLAR_PREVIEW

/**
 * Shutdown the meter provider.
 */
// bool MeterProvider::Shutdown(std::chrono::microseconds timeout) noexcept
// {
//   return context_->Shutdown(timeout);
// }

/**
 * Force flush the meter provider.
 */
// bool MeterProvider::ForceFlush(std::chrono::microseconds timeout) noexcept
// {
//   return context_->ForceFlush(timeout);
// }

/**
 * Shutdown MeterContext when MeterProvider is destroyed.
 *
 */
MeterProvider::~MeterProvider()
{
}

}  // namespace metrics
}  // namespace sdk
}  // namespace opentelemetry
