// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21402480;
  double density_weight = 0.26513907;
  double prefix_weight = 0.27412871;
  double neighborhood_weight = 0.02963296;
  double late_weight = 0.03002043;
  double critical_weight = 0.07894922;
  unsigned budget = 11;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
