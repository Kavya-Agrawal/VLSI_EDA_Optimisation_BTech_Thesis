// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13574749;
  double density_weight = 0.20351736;
  double prefix_weight = 0.06171490;
  double neighborhood_weight = 0.15397783;
  double late_weight = 0.10420134;
  double critical_weight = 0.43944804;
  unsigned budget = 10;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
