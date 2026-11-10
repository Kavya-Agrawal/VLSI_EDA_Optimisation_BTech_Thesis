// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40985354;
  double density_weight = 0.09916194;
  double prefix_weight = 0.28084434;
  double neighborhood_weight = 0.12395461;
  double late_weight = 0.27923130;
  double critical_weight = 0.39632294;
  unsigned budget = 37;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
