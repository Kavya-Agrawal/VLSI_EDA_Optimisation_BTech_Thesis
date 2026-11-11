// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98339178;
  double density_weight = 0.27660587;
  double prefix_weight = 0.48363508;
  double neighborhood_weight = 0.10897886;
  double late_weight = 0.12328780;
  double critical_weight = 0.46811752;
  unsigned budget = 32;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
