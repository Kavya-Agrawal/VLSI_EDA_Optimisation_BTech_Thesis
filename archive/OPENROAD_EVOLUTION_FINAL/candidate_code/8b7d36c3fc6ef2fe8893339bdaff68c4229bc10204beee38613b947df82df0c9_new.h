// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04269089;
  double density_weight = 0.49180638;
  double prefix_weight = 0.37249714;
  double neighborhood_weight = 0.01706690;
  double late_weight = 0.15632836;
  double critical_weight = 0.10016589;
  unsigned budget = 31;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
