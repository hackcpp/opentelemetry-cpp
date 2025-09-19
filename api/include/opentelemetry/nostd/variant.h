// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "boost/variant.hpp"
#include <type_traits>
#include <utility>

namespace opentelemetry {
namespace nostd
{
// nostd::variant<...>
template <class... _Types>
using variant = boost::variant<_Types...>;

using boost::get;

template <typename T, typename Variant>
bool holds_alternative(const Variant& v) {
    return boost::get<T>(&v) != nullptr;
}

// template <typename Visitor, typename Variant>
// auto visit(Visitor &&visitor, Variant &v) -> decltype(boost::apply_visitor(std::forward<Visitor>(visitor), v)) {
//     return boost::apply_visitor(std::forward<Visitor>(visitor), v);
// }

// template <typename Visitor, typename Variant>
// auto visit(Visitor &&visitor, const Variant &v) -> decltype(boost::apply_visitor(std::forward<Visitor>(visitor), v)) {
//     return boost::apply_visitor(std::forward<Visitor>(visitor), v);
// }


} // namespace nostd
} // namespace opentelemetry
