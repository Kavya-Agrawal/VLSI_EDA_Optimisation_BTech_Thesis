// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75028250;
  double density_weight = 0.10201815;
  double prefix_weight = 0.08179770;
  double neighborhood_weight = 0.05705151;
  double late_weight = 0.09072522;
  double critical_weight = 0.08098564;
  unsigned budget = 33;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
