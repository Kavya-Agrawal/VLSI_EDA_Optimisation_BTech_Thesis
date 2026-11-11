// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88695507;
  double density_weight = 0.23192365;
  double prefix_weight = 0.40216375;
  double neighborhood_weight = 0.05096788;
  double late_weight = 0.27993323;
  double critical_weight = 0.44243505;
  unsigned budget = 7;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
