// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21608715;
  double density_weight = 0.16614382;
  double prefix_weight = 0.40506914;
  double neighborhood_weight = 0.28293420;
  double late_weight = 0.25813996;
  double critical_weight = 0.15589968;
  unsigned budget = 7;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
