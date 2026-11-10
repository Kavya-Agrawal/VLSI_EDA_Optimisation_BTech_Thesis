// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84861922;
  double density_weight = 0.59239422;
  double prefix_weight = 0.36279443;
  double neighborhood_weight = 0.04103885;
  double late_weight = 0.28539575;
  double critical_weight = 0.41024958;
  unsigned budget = 35;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
