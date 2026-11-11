// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34812425;
  double density_weight = 0.37249238;
  double prefix_weight = 0.40269709;
  double neighborhood_weight = 0.17196794;
  double late_weight = 0.03552114;
  double critical_weight = 0.32748758;
  unsigned budget = 19;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
