// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37917280;
  double density_weight = 0.48708090;
  double prefix_weight = 0.10593851;
  double neighborhood_weight = 0.26013306;
  double late_weight = 0.06121332;
  double critical_weight = 0.09386738;
  unsigned budget = 39;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
