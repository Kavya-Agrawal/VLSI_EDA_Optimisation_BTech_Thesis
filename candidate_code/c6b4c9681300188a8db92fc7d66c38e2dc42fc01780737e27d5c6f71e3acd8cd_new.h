// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59494373;
  double density_weight = 0.10347532;
  double prefix_weight = 0.07019123;
  double neighborhood_weight = 0.21434744;
  double late_weight = 0.01756543;
  double critical_weight = 0.19877197;
  unsigned budget = 31;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
