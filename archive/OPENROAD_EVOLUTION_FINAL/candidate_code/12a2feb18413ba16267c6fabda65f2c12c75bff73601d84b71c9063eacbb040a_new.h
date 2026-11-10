// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90533691;
  double density_weight = 0.23110527;
  double prefix_weight = 0.36736763;
  double neighborhood_weight = 0.25145100;
  double late_weight = 0.19257844;
  double critical_weight = 0.49074477;
  unsigned budget = 10;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
