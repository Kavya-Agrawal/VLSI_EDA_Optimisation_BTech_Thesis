// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13326279;
  double density_weight = 0.04557472;
  double prefix_weight = 0.11972288;
  double neighborhood_weight = 0.28467308;
  double late_weight = 0.06021303;
  double critical_weight = 0.02063584;
  unsigned budget = 17;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
