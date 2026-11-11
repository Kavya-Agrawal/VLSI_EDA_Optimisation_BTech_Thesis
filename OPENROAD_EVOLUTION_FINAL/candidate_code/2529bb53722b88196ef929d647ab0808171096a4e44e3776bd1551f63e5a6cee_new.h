// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54045441;
  double density_weight = 0.44224054;
  double prefix_weight = 0.47217055;
  double neighborhood_weight = 0.18550707;
  double late_weight = 0.28750854;
  double critical_weight = 0.18440922;
  unsigned budget = 8;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
