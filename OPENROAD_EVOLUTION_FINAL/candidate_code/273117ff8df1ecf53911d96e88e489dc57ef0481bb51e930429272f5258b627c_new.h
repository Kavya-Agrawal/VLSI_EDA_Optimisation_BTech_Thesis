// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97596349;
  double density_weight = 0.25076984;
  double prefix_weight = 0.37212330;
  double neighborhood_weight = 0.13895534;
  double late_weight = 0.00649378;
  double critical_weight = 0.13756474;
  unsigned budget = 15;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
