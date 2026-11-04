// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88512001;
  double density_weight = 0.30123370;
  double prefix_weight = 0.25011399;
  double neighborhood_weight = 0.02246062;
  double late_weight = 0.08277160;
  double critical_weight = 0.32604283;
  unsigned budget = 38;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
