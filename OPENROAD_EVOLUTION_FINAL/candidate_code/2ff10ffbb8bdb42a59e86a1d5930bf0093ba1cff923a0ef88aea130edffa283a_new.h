// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59211254;
  double density_weight = 0.13788712;
  double prefix_weight = 0.06329369;
  double neighborhood_weight = 0.28081690;
  double late_weight = 0.16960632;
  double critical_weight = 0.03533515;
  unsigned budget = 27;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
