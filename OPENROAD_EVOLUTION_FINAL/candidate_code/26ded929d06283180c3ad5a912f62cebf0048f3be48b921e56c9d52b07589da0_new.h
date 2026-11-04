// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56106728;
  double density_weight = 0.24558633;
  double prefix_weight = 0.15518930;
  double neighborhood_weight = 0.04813059;
  double late_weight = 0.21236547;
  double critical_weight = 0.05594621;
  unsigned budget = 37;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
