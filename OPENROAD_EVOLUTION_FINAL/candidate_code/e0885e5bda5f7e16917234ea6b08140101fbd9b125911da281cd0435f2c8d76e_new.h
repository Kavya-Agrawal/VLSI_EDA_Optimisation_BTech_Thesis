// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41763566;
  double density_weight = 0.08236828;
  double prefix_weight = 0.31868626;
  double neighborhood_weight = 0.09676528;
  double late_weight = 0.28696059;
  double critical_weight = 0.18486591;
  unsigned budget = 27;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
