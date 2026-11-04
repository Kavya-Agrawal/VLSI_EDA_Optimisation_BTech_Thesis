// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03678676;
  double density_weight = 0.02236294;
  double prefix_weight = 0.12109181;
  double neighborhood_weight = 0.02035057;
  double late_weight = 0.10554065;
  double critical_weight = 0.05224649;
  unsigned budget = 5;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
