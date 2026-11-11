// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31048883;
  double density_weight = 0.55494543;
  double prefix_weight = 0.45322280;
  double neighborhood_weight = 0.31552119;
  double late_weight = 0.24829442;
  double critical_weight = 0.42552223;
  unsigned budget = 27;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
