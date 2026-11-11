// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94902591;
  double density_weight = 0.46279376;
  double prefix_weight = 0.40506520;
  double neighborhood_weight = 0.39108346;
  double late_weight = 0.02918959;
  double critical_weight = 0.41134601;
  unsigned budget = 37;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
