// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72705494;
  double density_weight = 0.25084504;
  double prefix_weight = 0.03432803;
  double neighborhood_weight = 0.23029572;
  double late_weight = 0.09916138;
  double critical_weight = 0.18982161;
  unsigned budget = 7;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
