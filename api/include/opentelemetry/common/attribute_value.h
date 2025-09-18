// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

// #include "opentelemetry/nostd/span.h"
// #include "opentelemetry/nostd/string_view.h"
// #include "opentelemetry/nostd/variant.h"
// #include "opentelemetry/version.h"

namespace opentelemetry {
namespace common
{
/// OpenTelemetry signals can be enriched by adding attributes. The
/// \c AttributeValue type is defined as a variant of all attribute value
/// types the OpenTelemetry C++ API supports.
///
/// The following attribute value types are supported by the OpenTelemetry
/// specification:
///  - Primitive types: string, boolean, double precision floating point
///    (IEEE 754-1985) or signed 64 bit integer.
///  - Homogenous arrays of primitive type values.
///
/// \warning The OpenTelemetry C++ API does not support the following attribute:
///  uint64_t, nostd::span<const uint64_t>, and nostd::span<const uint8_t> types.
/// \parblock The OpenTelemetry C++ API currently supports several attribute
/// value types that are not covered by the OpenTelemetry specification:
///  - \c uint64_t
///  - \c nostd::span<const uint64_t>
///  - \c nostd::span<const uint8_t>
///
/// Those types are reserved for future use and currently should not be
/// used. There are no guarantees around how those values are handled by
/// exporters.
/// \endparblock
using AttributeValue = std::string;

enum AttributeType
{
  kTypeBool,
  kTypeInt,
  kTypeInt64,
  kTypeUInt,
  kTypeDouble,
  kTypeCString,
  kTypeString,
  kTypeSpanBool,
  kTypeSpanInt,
  kTypeSpanInt64,
  kTypeSpanUInt,
  kTypeSpanDouble,
  kTypeSpanString,
  kTypeUInt64,
  kTypeSpanUInt64,
  kTypeSpanByte
};

}  // namespace common
}  // namespace opentelemetry
