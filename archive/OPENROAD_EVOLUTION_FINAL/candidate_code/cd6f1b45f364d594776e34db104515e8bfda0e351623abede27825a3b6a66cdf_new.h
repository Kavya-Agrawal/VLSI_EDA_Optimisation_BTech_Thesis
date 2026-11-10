// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21865432;
  double density_weight = 0.14150318;
  double prefix_weight = 0.17442987;
  double neighborhood_weight = 0.07089079;
  double late_weight = 0.06913732;
  double critical_weight = 0.00271509;
  unsigned budget = 27;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
