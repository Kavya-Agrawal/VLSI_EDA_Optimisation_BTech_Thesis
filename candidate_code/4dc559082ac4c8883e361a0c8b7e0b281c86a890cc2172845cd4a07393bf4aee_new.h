// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11662295;
  double density_weight = 0.25917929;
  double prefix_weight = 0.24943825;
  double neighborhood_weight = 0.24812499;
  double late_weight = 0.18791017;
  double critical_weight = 0.35386130;
  unsigned budget = 15;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
