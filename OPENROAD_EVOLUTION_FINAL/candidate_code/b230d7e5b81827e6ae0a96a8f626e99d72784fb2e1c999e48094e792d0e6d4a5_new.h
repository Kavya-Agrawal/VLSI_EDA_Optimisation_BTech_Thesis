// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66592872;
  double density_weight = 0.57342459;
  double prefix_weight = 0.24180915;
  double neighborhood_weight = 0.04644320;
  double late_weight = 0.25698493;
  double critical_weight = 0.39529209;
  unsigned budget = 34;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
