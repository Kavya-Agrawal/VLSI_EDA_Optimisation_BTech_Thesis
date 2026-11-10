// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98446147;
  double density_weight = 0.41780771;
  double prefix_weight = 0.02172534;
  double neighborhood_weight = 0.17447091;
  double late_weight = 0.29921372;
  double critical_weight = 0.37505391;
  unsigned budget = 19;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
