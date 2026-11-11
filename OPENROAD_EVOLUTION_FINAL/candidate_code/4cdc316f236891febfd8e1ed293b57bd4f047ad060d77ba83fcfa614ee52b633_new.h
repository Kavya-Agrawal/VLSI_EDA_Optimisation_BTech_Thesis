// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67173205;
  double density_weight = 0.36008811;
  double prefix_weight = 0.13338391;
  double neighborhood_weight = 0.27181006;
  double late_weight = 0.23396946;
  double critical_weight = 0.29965706;
  unsigned budget = 12;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
