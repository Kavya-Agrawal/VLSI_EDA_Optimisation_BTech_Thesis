// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13341512;
  double density_weight = 0.01886250;
  double prefix_weight = 0.28926205;
  double neighborhood_weight = 0.06658803;
  double late_weight = 0.07242673;
  double critical_weight = 0.23948885;
  unsigned budget = 36;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
