// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11607559;
  double density_weight = 0.13273692;
  double prefix_weight = 0.05127653;
  double neighborhood_weight = 0.11294526;
  double late_weight = 0.23127492;
  double critical_weight = 0.38606941;
  unsigned budget = 7;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
