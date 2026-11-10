// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79706233;
  double density_weight = 0.39809679;
  double prefix_weight = 0.15568580;
  double neighborhood_weight = 0.05823524;
  double late_weight = 0.09058899;
  double critical_weight = 0.25231807;
  unsigned budget = 15;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
