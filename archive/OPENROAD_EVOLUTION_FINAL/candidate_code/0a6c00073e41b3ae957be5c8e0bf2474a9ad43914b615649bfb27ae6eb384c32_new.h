// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27736139;
  double density_weight = 0.11587520;
  double prefix_weight = 0.27775258;
  double neighborhood_weight = 0.01801612;
  double late_weight = 0.26625827;
  double critical_weight = 0.47775197;
  unsigned budget = 28;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
