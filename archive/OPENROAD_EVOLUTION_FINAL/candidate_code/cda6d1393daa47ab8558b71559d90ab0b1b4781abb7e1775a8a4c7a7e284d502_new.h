// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20782336;
  double density_weight = 0.16451416;
  double prefix_weight = 0.36102760;
  double neighborhood_weight = 0.37345589;
  double late_weight = 0.16365433;
  double critical_weight = 0.22341856;
  unsigned budget = 11;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
