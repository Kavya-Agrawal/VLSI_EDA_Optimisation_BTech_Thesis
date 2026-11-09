// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65082134;
  double density_weight = 0.22234394;
  double prefix_weight = 0.08385523;
  double neighborhood_weight = 0.02069575;
  double late_weight = 0.06146805;
  double critical_weight = 0.20955336;
  unsigned budget = 17;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
