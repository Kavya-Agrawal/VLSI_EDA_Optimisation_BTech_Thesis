// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97437038;
  double density_weight = 0.52268397;
  double prefix_weight = 0.36211408;
  double neighborhood_weight = 0.09200712;
  double late_weight = 0.19566806;
  double critical_weight = 0.33547806;
  unsigned budget = 9;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
