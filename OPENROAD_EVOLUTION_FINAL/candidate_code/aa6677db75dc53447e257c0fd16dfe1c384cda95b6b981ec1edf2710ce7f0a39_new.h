// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20040152;
  double density_weight = 0.15195418;
  double prefix_weight = 0.42490869;
  double neighborhood_weight = 0.02445627;
  double late_weight = 0.02106763;
  double critical_weight = 0.48817996;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
