// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83998600;
  double density_weight = 0.26355812;
  double prefix_weight = 0.14378251;
  double neighborhood_weight = 0.09418713;
  double late_weight = 0.17608485;
  double critical_weight = 0.17196252;
  unsigned budget = 18;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
