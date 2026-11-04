// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73557148;
  double density_weight = 0.38807124;
  double prefix_weight = 0.45631113;
  double neighborhood_weight = 0.14502531;
  double late_weight = 0.22694845;
  double critical_weight = 0.13514248;
  unsigned budget = 29;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
