// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13008853;
  double density_weight = 0.19486800;
  double prefix_weight = 0.46295505;
  double neighborhood_weight = 0.10883348;
  double late_weight = 0.13549644;
  double critical_weight = 0.43673170;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
