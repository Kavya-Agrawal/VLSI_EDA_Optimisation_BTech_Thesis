// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94600858;
  double density_weight = 0.18711651;
  double prefix_weight = 0.19826852;
  double neighborhood_weight = 0.10233028;
  double late_weight = 0.05785916;
  double critical_weight = 0.47521118;
  unsigned budget = 22;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
