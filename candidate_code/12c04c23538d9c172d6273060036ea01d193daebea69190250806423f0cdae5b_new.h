// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65814648;
  double density_weight = 0.11400371;
  double prefix_weight = 0.49873317;
  double neighborhood_weight = 0.10669288;
  double late_weight = 0.28475639;
  double critical_weight = 0.18385025;
  unsigned budget = 10;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
