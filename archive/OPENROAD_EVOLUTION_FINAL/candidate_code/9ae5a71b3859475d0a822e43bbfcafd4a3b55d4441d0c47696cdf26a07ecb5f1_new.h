// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36047464;
  double density_weight = 0.00851437;
  double prefix_weight = 0.41887207;
  double neighborhood_weight = 0.03281699;
  double late_weight = 0.11808728;
  double critical_weight = 0.49757629;
  unsigned budget = 35;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
