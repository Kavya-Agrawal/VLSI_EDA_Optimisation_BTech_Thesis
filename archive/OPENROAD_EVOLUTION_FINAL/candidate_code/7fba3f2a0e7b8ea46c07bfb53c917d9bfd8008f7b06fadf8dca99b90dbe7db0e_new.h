// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75712482;
  double density_weight = 0.44981680;
  double prefix_weight = 0.37358533;
  double neighborhood_weight = 0.35846251;
  double late_weight = 0.27418146;
  double critical_weight = 0.47753956;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
