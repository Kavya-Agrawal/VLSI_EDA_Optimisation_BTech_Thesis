// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85189852;
  double density_weight = 0.36860261;
  double prefix_weight = 0.38617235;
  double neighborhood_weight = 0.33238138;
  double late_weight = 0.02862933;
  double critical_weight = 0.16882261;
  unsigned budget = 29;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
