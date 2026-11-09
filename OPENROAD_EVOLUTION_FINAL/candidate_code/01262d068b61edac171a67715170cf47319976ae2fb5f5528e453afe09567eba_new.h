// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47241121;
  double density_weight = 0.24137535;
  double prefix_weight = 0.32876994;
  double neighborhood_weight = 0.15281405;
  double late_weight = 0.12884752;
  double critical_weight = 0.34701785;
  unsigned budget = 5;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
