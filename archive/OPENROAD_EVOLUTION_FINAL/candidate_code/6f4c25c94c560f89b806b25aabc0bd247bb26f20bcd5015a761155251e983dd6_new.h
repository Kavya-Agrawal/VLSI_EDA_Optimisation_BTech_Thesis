// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09106285;
  double density_weight = 0.02017902;
  double prefix_weight = 0.25102348;
  double neighborhood_weight = 0.08641129;
  double late_weight = 0.01536740;
  double critical_weight = 0.18481834;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
