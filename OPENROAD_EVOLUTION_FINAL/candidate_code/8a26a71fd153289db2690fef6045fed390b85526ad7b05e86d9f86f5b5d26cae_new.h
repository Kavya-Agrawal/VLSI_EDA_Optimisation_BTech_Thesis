// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03805853;
  double density_weight = 0.41104321;
  double prefix_weight = 0.23636799;
  double neighborhood_weight = 0.32551624;
  double late_weight = 0.10132103;
  double critical_weight = 0.19602198;
  unsigned budget = 19;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
