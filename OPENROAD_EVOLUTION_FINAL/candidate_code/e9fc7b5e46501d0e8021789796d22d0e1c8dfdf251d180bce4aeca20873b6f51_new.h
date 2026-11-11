// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18189147;
  double density_weight = 0.00128498;
  double prefix_weight = 0.37760624;
  double neighborhood_weight = 0.06770278;
  double late_weight = 0.20854308;
  double critical_weight = 0.35372381;
  unsigned budget = 28;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
