// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22894218;
  double density_weight = 0.27047197;
  double prefix_weight = 0.46159246;
  double neighborhood_weight = 0.14347333;
  double late_weight = 0.24355917;
  double critical_weight = 0.46907934;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
