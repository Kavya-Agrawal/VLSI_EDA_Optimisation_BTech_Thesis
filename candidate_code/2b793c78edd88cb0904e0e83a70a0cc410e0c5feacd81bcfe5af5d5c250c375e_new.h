// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18775802;
  double density_weight = 0.33693652;
  double prefix_weight = 0.21129007;
  double neighborhood_weight = 0.37872901;
  double late_weight = 0.18270758;
  double critical_weight = 0.28070797;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
