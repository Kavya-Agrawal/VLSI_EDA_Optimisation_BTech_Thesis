// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62966204;
  double density_weight = 0.49391375;
  double prefix_weight = 0.01895128;
  double neighborhood_weight = 0.20307970;
  double late_weight = 0.27524145;
  double critical_weight = 0.02137787;
  unsigned budget = 36;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
