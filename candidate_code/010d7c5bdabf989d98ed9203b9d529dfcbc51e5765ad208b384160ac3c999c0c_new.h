// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00139881;
  double density_weight = 0.27723925;
  double prefix_weight = 0.08944130;
  double neighborhood_weight = 0.20602307;
  double late_weight = 0.21284940;
  double critical_weight = 0.23995387;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
