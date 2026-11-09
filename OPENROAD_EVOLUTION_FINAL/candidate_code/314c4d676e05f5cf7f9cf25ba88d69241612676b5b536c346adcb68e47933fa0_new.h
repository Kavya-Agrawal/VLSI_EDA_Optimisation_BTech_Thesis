// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10737426;
  double density_weight = 0.43234487;
  double prefix_weight = 0.33252687;
  double neighborhood_weight = 0.39885787;
  double late_weight = 0.00451914;
  double critical_weight = 0.48212177;
  unsigned budget = 26;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
