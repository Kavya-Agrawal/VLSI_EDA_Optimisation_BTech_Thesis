// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79831442;
  double density_weight = 0.17520943;
  double prefix_weight = 0.47900124;
  double neighborhood_weight = 0.19214679;
  double late_weight = 0.26546867;
  double critical_weight = 0.25544851;
  unsigned budget = 9;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
