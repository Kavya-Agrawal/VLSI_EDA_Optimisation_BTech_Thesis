// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69451172;
  double density_weight = 0.55883579;
  double prefix_weight = 0.05151285;
  double neighborhood_weight = 0.29237115;
  double late_weight = 0.28149404;
  double critical_weight = 0.45153168;
  unsigned budget = 31;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
