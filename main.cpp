#include <iostream>
#include "opentelemetry/sdk/metrics/meter_context_factory.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"
#include "opentelemetry/metrics/meter.h"
#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/common/key_value_iterable_view.h"


using namespace opentelemetry::sdk::metrics;

int main() {
  std::cout << "Testing OpenTelemetry C++ SDK\n";
  
  // 创建 Meter 示例
  auto meter_context = MeterContextFactory::Create();
  auto meter_privoder = MeterProviderFactory::Create(std::move(meter_context));

  auto meter = meter_privoder->GetMeter("bonree");
  auto histogram = meter->CreateUInt64Histogram("http.server.duration", "measures the duration of the inbound HTTP request", "us");

  std::map<std::string, std::string> labels = {
      {"http.method", "GET"}, 
      {"http.status_code", rand() % 2 ? "200" : "300"}};
  auto labelkv = opentelemetry::common::KeyValueIterableView<decltype(labels)>{labels};
  histogram->Record(123, labelkv);
  
  return 0;
}