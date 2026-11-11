// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97870690;
  double density_weight = 0.52492615;
  double prefix_weight = 0.35655693;
  double neighborhood_weight = 0.18320974;
  double late_weight = 0.07151831;
  double critical_weight = 0.11530547;
  unsigned budget = 34;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
