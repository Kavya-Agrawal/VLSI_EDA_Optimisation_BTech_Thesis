// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00357422;
  double density_weight = 0.11880161;
  double prefix_weight = 0.06030668;
  double neighborhood_weight = 0.14042510;
  double late_weight = 0.06023649;
  double critical_weight = 0.00603915;
  unsigned budget = 25;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
