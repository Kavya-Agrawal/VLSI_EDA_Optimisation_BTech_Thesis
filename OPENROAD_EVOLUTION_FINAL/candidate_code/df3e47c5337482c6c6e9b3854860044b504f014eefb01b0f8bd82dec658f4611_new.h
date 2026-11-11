// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92475062;
  double density_weight = 0.48597230;
  double prefix_weight = 0.41755966;
  double neighborhood_weight = 0.07323842;
  double late_weight = 0.17039868;
  double critical_weight = 0.25252606;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
