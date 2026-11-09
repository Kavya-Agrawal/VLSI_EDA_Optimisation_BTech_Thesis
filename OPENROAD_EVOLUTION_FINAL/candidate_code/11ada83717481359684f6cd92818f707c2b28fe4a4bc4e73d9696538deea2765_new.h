// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70074632;
  double density_weight = 0.24827929;
  double prefix_weight = 0.42487903;
  double neighborhood_weight = 0.08439169;
  double late_weight = 0.12341335;
  double critical_weight = 0.33801055;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
