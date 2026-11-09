// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89469464;
  double density_weight = 0.33129570;
  double prefix_weight = 0.15828617;
  double neighborhood_weight = 0.01298325;
  double late_weight = 0.22030669;
  double critical_weight = 0.30811622;
  unsigned budget = 28;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
