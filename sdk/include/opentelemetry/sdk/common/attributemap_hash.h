// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stddef.h>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "opentelemetry/sdk/common/attribute_utils.h"
#include "opentelemetry/nostd/variant.h"

namespace opentelemetry {
namespace sdk
{
namespace common
{

template <class T>
inline void GetHash(size_t &seed, const T &arg)
{
  std::hash<T> hasher;
  // reference -
  // https://www.boost.org/doc/libs/1_37_0/doc/html/hash/reference.html#boost.hash_combine
  seed ^= hasher(arg) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <class T>
inline void GetHash(size_t &seed, const std::vector<T> &arg)
{
  for (auto v : arg)
  {
    GetHash<T>(seed, v);
  }
}

// Specialization for const char*
// this creates an intermediate string.
template <>
inline void GetHash<const char *>(size_t &seed, const char *const &arg)
{
  std::hash<std::string> hasher;
  seed ^= hasher(std::string(arg)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct GetHashForAttributeValueVisitor
{
  GetHashForAttributeValueVisitor(size_t &seed) : seed_(seed) {}
  void operator()(const OwnedAttributeValue& value )
  {
    if (nostd::holds_alternative<bool>(value))
    {
       GetHash(seed_, nostd::get<bool>(value));
    }
    else if (nostd::holds_alternative<int>(value))
    {
      GetHash(seed_, nostd::get<int>(value));
    }
    else if (nostd::holds_alternative<int64_t>(value))
    {
      GetHash(seed_, nostd::get<int64_t>(value));
    }
    else if (nostd::holds_alternative<unsigned int>(value))
    {
      GetHash(seed_, nostd::get<unsigned int>(value));
    }
    else if (nostd::holds_alternative<uint64_t>(value))
    {
      GetHash(seed_, nostd::get<uint64_t>(value));
    }
    else if (nostd::holds_alternative<double>(value))
    {
      GetHash(seed_, nostd::get<double>(value));
    }
    else if (nostd::holds_alternative<std::string>(value))
    {
      GetHash(seed_, nostd::get<std::string>(value));
    }
  }
  size_t &seed_;
};

// Calculate hash of keys and values of attribute map
inline size_t GetHashForAttributeMap(const OrderedAttributeMap &attribute_map)
{
  size_t seed = 0UL;
  for (auto &kv : attribute_map)
  {
    GetHash(seed, kv.first);
    // opentelemetry::nostd::visit(GetHashForAttributeValueVisitor(seed), kv.second);
    GetHashForAttributeValueVisitor(seed).operator()(kv.second);
  }
  return seed;
}

// template <class T>
// inline size_t GetHash(T value)
// {
//   std::hash<T> hasher;
//   return hasher(value);
// }

}  // namespace common
}  // namespace sdk
}
