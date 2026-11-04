// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85488403;
  double density_weight = 0.40403334;
  double prefix_weight = 0.44699207;
  double neighborhood_weight = 0.05776874;
  double late_weight = 0.09106514;
  double critical_weight = 0.45989341;
  unsigned budget = 20;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
