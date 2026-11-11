// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36303966;
  double density_weight = 0.04267203;
  double prefix_weight = 0.36814617;
  double neighborhood_weight = 0.16824313;
  double late_weight = 0.02762433;
  double critical_weight = 0.16391035;
  unsigned budget = 34;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
