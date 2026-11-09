// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77820832;
  double density_weight = 0.37112433;
  double prefix_weight = 0.25871824;
  double neighborhood_weight = 0.27008134;
  double late_weight = 0.04217545;
  double critical_weight = 0.39407539;
  unsigned budget = 33;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
