// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43938283;
  double density_weight = 0.07918074;
  double prefix_weight = 0.04171980;
  double neighborhood_weight = 0.39035594;
  double late_weight = 0.03548255;
  double critical_weight = 0.18088254;
  unsigned budget = 12;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
