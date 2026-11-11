// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27009195;
  double density_weight = 0.41842107;
  double prefix_weight = 0.17490221;
  double neighborhood_weight = 0.01986876;
  double late_weight = 0.07911447;
  double critical_weight = 0.22462965;
  unsigned budget = 29;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
