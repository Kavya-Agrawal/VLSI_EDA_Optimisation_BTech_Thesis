// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56402620;
  double density_weight = 0.13694193;
  double prefix_weight = 0.06797775;
  double neighborhood_weight = 0.37994290;
  double late_weight = 0.27684082;
  double critical_weight = 0.19525014;
  unsigned budget = 32;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
