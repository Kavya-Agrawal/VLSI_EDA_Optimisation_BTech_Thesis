// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81429812;
  double density_weight = 0.04658682;
  double prefix_weight = 0.22883709;
  double neighborhood_weight = 0.05016656;
  double late_weight = 0.27854495;
  double critical_weight = 0.49625023;
  unsigned budget = 14;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
