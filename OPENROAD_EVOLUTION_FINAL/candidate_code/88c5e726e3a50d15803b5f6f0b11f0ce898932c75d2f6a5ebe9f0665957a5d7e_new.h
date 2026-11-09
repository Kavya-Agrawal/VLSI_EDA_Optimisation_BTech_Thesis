// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27097874;
  double density_weight = 0.55536817;
  double prefix_weight = 0.04989015;
  double neighborhood_weight = 0.14013743;
  double late_weight = 0.03223466;
  double critical_weight = 0.30286759;
  unsigned budget = 7;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
