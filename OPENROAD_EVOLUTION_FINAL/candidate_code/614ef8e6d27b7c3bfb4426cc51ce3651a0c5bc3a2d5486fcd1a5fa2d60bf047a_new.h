// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53655802;
  double density_weight = 0.37081194;
  double prefix_weight = 0.02409363;
  double neighborhood_weight = 0.08058669;
  double late_weight = 0.17336193;
  double critical_weight = 0.26852112;
  unsigned budget = 11;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
