// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41686916;
  double density_weight = 0.19143222;
  double prefix_weight = 0.04054296;
  double neighborhood_weight = 0.04601701;
  double late_weight = 0.21086757;
  double critical_weight = 0.05333616;
  unsigned budget = 27;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
