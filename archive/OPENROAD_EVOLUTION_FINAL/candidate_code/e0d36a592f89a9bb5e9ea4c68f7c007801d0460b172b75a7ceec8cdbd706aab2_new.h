// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43348154;
  double density_weight = 0.15926119;
  double prefix_weight = 0.28452225;
  double neighborhood_weight = 0.16780585;
  double late_weight = 0.22379866;
  double critical_weight = 0.15879730;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
