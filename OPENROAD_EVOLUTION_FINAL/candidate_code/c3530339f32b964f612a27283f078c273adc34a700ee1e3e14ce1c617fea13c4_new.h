// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62329994;
  double density_weight = 0.26859738;
  double prefix_weight = 0.20470401;
  double neighborhood_weight = 0.33490620;
  double late_weight = 0.03726820;
  double critical_weight = 0.15910150;
  unsigned budget = 10;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
