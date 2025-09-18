// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/common/key_value_iterable.h"

namespace opentelemetry {
namespace metrics
{

class SynchronousInstrument
{
public:
  SynchronousInstrument()          = default;
  virtual ~SynchronousInstrument() = default;
};


/** A histogram instrument that records values. */
template <class T>
class Histogram : public SynchronousInstrument
{
public:
 /**
   * @since ABI_VERSION 2
   * Records a value.
   *
   * @param value The measurement value. MUST be non-negative.
   */
  virtual void Record(T value) noexcept = 0;

  /**
   * @since ABI_VERSION 2
   * Records a value with a set of attributes.
   *
   * @param value The measurement value. MUST be non-negative.
   * @param attribute A set of attributes to associate with the value.
   */
  virtual void Record(T value, const common::KeyValueIterable &attribute) noexcept = 0;

  // template <class U,
  //           nostd::enable_if_t<common::detail::is_key_value_iterable<U>::value> * = nullptr>
  // void Record(T value, const U &attributes) noexcept
  // {
  //   this->Record(value, common::KeyValueIterableView<U>{attributes});
  // }

  // void Record(T value,
  //             std::initializer_list<std::pair<nostd::string_view, common::AttributeValue>>
  //                 attributes) noexcept
  // {
  //   this->Record(value, nostd::span<const std::pair<nostd::string_view, common::AttributeValue>>{
  //                           attributes.begin(), attributes.end()});
  // }
};

}
}