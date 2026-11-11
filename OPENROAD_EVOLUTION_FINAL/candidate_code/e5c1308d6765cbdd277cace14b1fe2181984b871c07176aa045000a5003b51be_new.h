// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81566501;
  double density_weight = 0.32837571;
  double prefix_weight = 0.49578824;
  double neighborhood_weight = 0.06904187;
  double late_weight = 0.07864626;
  double critical_weight = 0.45603205;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
