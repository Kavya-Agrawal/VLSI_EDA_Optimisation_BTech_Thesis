// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65396867;
  double density_weight = 0.23997035;
  double prefix_weight = 0.05942513;
  double neighborhood_weight = 0.08007556;
  double late_weight = 0.04519346;
  double critical_weight = 0.03074003;
  unsigned budget = 4;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
