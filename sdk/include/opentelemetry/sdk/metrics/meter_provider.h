// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <chrono>
#include <memory>
#include <mutex>

#include "opentelemetry/metrics/meter_provider.h"
#include "opentelemetry/sdk/metrics/meter_context.h"

namespace opentelemetry {
namespace sdk
{
namespace metrics
{

class MeterProvider final : public opentelemetry::metrics::MeterProvider
{
public:
  /**
   * Initialize a new meter provider with a specified context
   * @param context The owned meter configuration/pipeline for this provider.
   */
  explicit MeterProvider(std::unique_ptr<MeterContext> context) noexcept;

  /*
    Make sure GetMeter() helpers from the API are seen in overload resolution.
  */
  std::shared_ptr<opentelemetry::metrics::Meter> GetMeter(const std::string &name,
                                  const std::string &version = "",
                                  const std::string &schema_url = "") noexcept override;

  /**
   * Obtain the resource associated with this meter provider.
   * @return The resource for this meter provider.
   */
  const sdk::resource::Resource &GetResource() const noexcept;

  /**
   * Create a MetricCollector from a MetricReader using the MeterContext of this MeterProvider and
   * add it to the list of configured collectors.
   * @param reader The MetricReader for which a MetricCollector is to be created. This must not be a
   * nullptr.
   * @param metric_filter The optional MetricFilter used when creating the MetricCollector.
   *
   * Note: This reader may not receive any in-flight meter data, but will get newly created meter
   * data.
   * Note: This method is not thread safe, and should ideally be called from main thread.
   */
  // void AddMetricReader(std::shared_ptr<MetricReader> reader,
  //                      std::unique_ptr<MetricFilter> metric_filter = nullptr) noexcept;

  /**
   * Attaches a View to list of configured Views for this Meter provider.
   * @param view The Views for this meter provider. This
   * must not be a nullptr.
   *
   * Note: This view may not receive any in-flight meter data, but will get newly created meter
   * data. Note: This method is not thread safe, and should ideally be called from main thread.
   */
//   void AddView(std::unique_ptr<InstrumentSelector> instrument_selector,
//                std::unique_ptr<MeterSelector> meter_selector,
//                std::unique_ptr<View> view) noexcept;

// #ifdef ENABLE_METRICS_EXEMPLAR_PREVIEW

//   void SetExemplarFilter(metrics::ExemplarFilterType exemplar_filter_type =
//                              metrics::ExemplarFilterType::kTraceBased) noexcept;

// #endif

  // /**
  //  * Shutdown the meter provider.
  //  */
  // bool Shutdown(std::chrono::microseconds timeout = (std::chrono::microseconds::max)()) noexcept;

  // /**
  //  * Force flush the meter provider.
  //  */
  // bool ForceFlush(std::chrono::microseconds timeout = (std::chrono::microseconds::max)()) noexcept;

  ~MeterProvider() override;

private:
  std::shared_ptr<MeterContext> context_;
  std::mutex lock_;
};

}  // namespace metrics
}  // namespace sdk
}  // namespace opentelemetry
