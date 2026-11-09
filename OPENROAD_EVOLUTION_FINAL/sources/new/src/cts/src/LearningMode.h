// SPDX-License-Identifier: BSD-3-Clause
#pragma once
#include <cstdlib>
#include <string_view>
namespace ord::learning {
inline bool enabled()
{
  const char* value = std::getenv("OPENROAD_LEARNING_EVOLUTION");
  return value != nullptr && std::string_view(value) == "1";
}
}  // namespace ord::learning
