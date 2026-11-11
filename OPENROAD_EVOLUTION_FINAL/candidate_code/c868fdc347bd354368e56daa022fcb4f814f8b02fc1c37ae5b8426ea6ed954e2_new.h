// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64336807;
  double density_weight = 0.50268166;
  double prefix_weight = 0.25338184;
  double neighborhood_weight = 0.34960607;
  double late_weight = 0.12487194;
  double critical_weight = 0.23078048;
  unsigned budget = 28;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
