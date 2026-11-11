// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50835163;
  double density_weight = 0.02973393;
  double prefix_weight = 0.10107751;
  double neighborhood_weight = 0.07243567;
  double late_weight = 0.14889450;
  double critical_weight = 0.41728246;
  unsigned budget = 35;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
