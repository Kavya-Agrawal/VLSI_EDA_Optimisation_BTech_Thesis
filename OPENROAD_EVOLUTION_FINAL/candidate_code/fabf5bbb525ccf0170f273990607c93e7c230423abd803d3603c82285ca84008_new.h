// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01949175;
  double density_weight = 0.22553505;
  double prefix_weight = 0.05428475;
  double neighborhood_weight = 0.15037882;
  double late_weight = 0.22799979;
  double critical_weight = 0.00246780;
  unsigned budget = 35;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
