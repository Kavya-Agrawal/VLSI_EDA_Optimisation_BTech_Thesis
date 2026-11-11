// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70266800;
  double density_weight = 0.31671756;
  double prefix_weight = 0.49987605;
  double neighborhood_weight = 0.34415735;
  double late_weight = 0.11656960;
  double critical_weight = 0.39602057;
  unsigned budget = 40;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
