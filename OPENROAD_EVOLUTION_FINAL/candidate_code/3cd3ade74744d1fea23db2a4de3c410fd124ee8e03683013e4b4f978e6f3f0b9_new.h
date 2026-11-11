// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31674165;
  double density_weight = 0.20030254;
  double prefix_weight = 0.40170430;
  double neighborhood_weight = 0.01654515;
  double late_weight = 0.29154202;
  double critical_weight = 0.28421851;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
