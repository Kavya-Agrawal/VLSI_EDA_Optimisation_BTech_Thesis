// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77589941;
  double density_weight = 0.52207528;
  double prefix_weight = 0.19710915;
  double neighborhood_weight = 0.35171317;
  double late_weight = 0.22982435;
  double critical_weight = 0.29050631;
  unsigned budget = 34;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
