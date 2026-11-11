// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94794495;
  double density_weight = 0.14441143;
  double prefix_weight = 0.22239224;
  double neighborhood_weight = 0.07421925;
  double late_weight = 0.20271627;
  double critical_weight = 0.07335958;
  unsigned budget = 35;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
