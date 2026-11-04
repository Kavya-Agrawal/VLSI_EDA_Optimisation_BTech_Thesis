// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74790100;
  double density_weight = 0.34297348;
  double prefix_weight = 0.45808739;
  double neighborhood_weight = 0.37818830;
  double late_weight = 0.17634401;
  double critical_weight = 0.26054626;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
