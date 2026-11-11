// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41497046;
  double density_weight = 0.56104618;
  double prefix_weight = 0.03443868;
  double neighborhood_weight = 0.08449515;
  double late_weight = 0.12316506;
  double critical_weight = 0.20213863;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
