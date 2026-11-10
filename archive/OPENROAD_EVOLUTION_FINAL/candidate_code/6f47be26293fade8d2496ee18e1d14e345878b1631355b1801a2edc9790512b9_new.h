// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55683992;
  double density_weight = 0.08400307;
  double prefix_weight = 0.12380473;
  double neighborhood_weight = 0.32280862;
  double late_weight = 0.19401666;
  double critical_weight = 0.19633297;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
