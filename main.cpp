#include <iostream>
#include "opentelemetry/sdk/metrics/meter_context_factory.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"
#include "opentelemetry/metrics/meter.h"
#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/common/key_value_iterable_view.h"
#include "opentelemetry/metrics/provider.h"
#include "opentelemetry/sdk/metrics/provider.h"

#include "opentelemetry/sdk/metrics/metric_reader.h"
#include "opentelemetry/exporters/otlp/otlp_metric_utils.h"
#include "opentelemetry/proto/collector/metrics/v1/metrics_service.pb.h"
#include "opentelemetry/proto/common/v1/common.pb.h"
#include "opentelemetry/proto/metrics/v1/metrics.pb.h"

using namespace opentelemetry::sdk::metrics;
using namespace opentelemetry::exporter::otlp;

std::shared_ptr<opentelemetry::sdk::metrics::MetricReader> reader = std::make_shared<opentelemetry::sdk::metrics::MetricReader>();

void init() {
  auto meter_context = MeterContextFactory::Create();
  meter_context->AddMetricReader(reader);
  auto meter_privoder = MeterProviderFactory::Create(std::move(meter_context));
  std::shared_ptr<opentelemetry::metrics::MeterProvider> api_provider(std::move(meter_privoder));
  opentelemetry::sdk::metrics::Provider::SetMeterProvider(api_provider);
}

int main() {
  init();
  std::cout << "Testing OpenTelemetry C++ SDK\n";
  
  // 创建 Meter 示例

  auto meter = opentelemetry::metrics::Provider::GetMeterProvider()->GetMeter("opentelemetry.instrumentation.bonree","5.12");
  auto histogram = meter->CreateUInt64Histogram("http.server.duration", "measures the duration of the inbound HTTP request", "us");

  for (int i = 0; i < 1; ++i)
  {
    std::map<std::string, std::string> labels = {
        {"http.method", "GET"},
        {"http.status_code", rand() % 2 ? "200" : "300"}};
    auto labelkv = opentelemetry::common::KeyValueIterableView<decltype(labels)>{labels};
    histogram->Record(rand(), labelkv);
  }

  reader->Collect([](ResourceMetrics &metric_data)->bool{
  opentelemetry::proto::collector::metrics::v1::ExportMetricsServiceRequest req;
    OtlpMetricUtils::PopulateRequest(metric_data, &req);
    std::cout << req.Utf8DebugString();
    return true;
  });
  
  return 0;
}