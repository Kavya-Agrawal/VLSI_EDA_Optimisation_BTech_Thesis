// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15091226;
  double density_weight = 0.00741086;
  double prefix_weight = 0.35130354;
  double neighborhood_weight = 0.28663615;
  double late_weight = 0.28474115;
  double critical_weight = 0.27989307;
  unsigned budget = 37;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
