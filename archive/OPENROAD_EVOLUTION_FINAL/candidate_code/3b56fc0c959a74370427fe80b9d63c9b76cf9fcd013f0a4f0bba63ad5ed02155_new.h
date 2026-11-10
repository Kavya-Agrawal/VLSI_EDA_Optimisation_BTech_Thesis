// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00704197;
  double density_weight = 0.41755365;
  double prefix_weight = 0.34808357;
  double neighborhood_weight = 0.32372297;
  double late_weight = 0.14812193;
  double critical_weight = 0.12591961;
  unsigned budget = 31;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
