// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46741598;
  double density_weight = 0.06044197;
  double prefix_weight = 0.48419216;
  double neighborhood_weight = 0.14148110;
  double late_weight = 0.09128092;
  double critical_weight = 0.34226181;
  unsigned budget = 25;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
