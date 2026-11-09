// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41737350;
  double density_weight = 0.13245509;
  double prefix_weight = 0.20789043;
  double neighborhood_weight = 0.20661825;
  double late_weight = 0.25714675;
  double critical_weight = 0.07539468;
  unsigned budget = 32;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
