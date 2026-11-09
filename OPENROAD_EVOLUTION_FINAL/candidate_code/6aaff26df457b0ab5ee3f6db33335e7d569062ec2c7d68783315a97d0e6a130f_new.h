// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52781471;
  double density_weight = 0.43829468;
  double prefix_weight = 0.24011885;
  double neighborhood_weight = 0.20962720;
  double late_weight = 0.12783787;
  double critical_weight = 0.34509373;
  unsigned budget = 17;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
