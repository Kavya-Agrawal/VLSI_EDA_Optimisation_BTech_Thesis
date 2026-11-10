// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11462762;
  double density_weight = 0.48109282;
  double prefix_weight = 0.43220767;
  double neighborhood_weight = 0.34069562;
  double late_weight = 0.24260631;
  double critical_weight = 0.24620966;
  unsigned budget = 19;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
