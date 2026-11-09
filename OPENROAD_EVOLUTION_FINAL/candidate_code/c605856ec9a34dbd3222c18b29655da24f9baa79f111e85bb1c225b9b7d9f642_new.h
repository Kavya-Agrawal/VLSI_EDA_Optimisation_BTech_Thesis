// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24681296;
  double density_weight = 0.56431756;
  double prefix_weight = 0.02873220;
  double neighborhood_weight = 0.29038095;
  double late_weight = 0.14050752;
  double critical_weight = 0.39692447;
  unsigned budget = 38;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
