// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72753086;
  double density_weight = 0.00628139;
  double prefix_weight = 0.09088794;
  double neighborhood_weight = 0.03807162;
  double late_weight = 0.14810616;
  double critical_weight = 0.44354430;
  unsigned budget = 39;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
