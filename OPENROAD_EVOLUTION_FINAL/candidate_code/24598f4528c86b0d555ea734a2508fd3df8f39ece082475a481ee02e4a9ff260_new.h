// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31642064;
  double density_weight = 0.12467238;
  double prefix_weight = 0.01384101;
  double neighborhood_weight = 0.26618310;
  double late_weight = 0.25510796;
  double critical_weight = 0.09687834;
  unsigned budget = 4;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
