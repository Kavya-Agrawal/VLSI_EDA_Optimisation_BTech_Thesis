// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80225718;
  double density_weight = 0.28732563;
  double prefix_weight = 0.49530740;
  double neighborhood_weight = 0.10717953;
  double late_weight = 0.08520431;
  double critical_weight = 0.17468822;
  unsigned budget = 7;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
