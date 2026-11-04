// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53912279;
  double density_weight = 0.12082737;
  double prefix_weight = 0.32550645;
  double neighborhood_weight = 0.21292498;
  double late_weight = 0.28715301;
  double critical_weight = 0.12468591;
  unsigned budget = 38;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
