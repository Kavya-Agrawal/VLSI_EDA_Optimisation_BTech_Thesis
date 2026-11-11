// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51854705;
  double density_weight = 0.30141999;
  double prefix_weight = 0.35792265;
  double neighborhood_weight = 0.38932133;
  double late_weight = 0.07069343;
  double critical_weight = 0.10062500;
  unsigned budget = 9;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
