// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19859297;
  double density_weight = 0.11697674;
  double prefix_weight = 0.33259281;
  double neighborhood_weight = 0.26392448;
  double late_weight = 0.19050860;
  double critical_weight = 0.20433203;
  unsigned budget = 38;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
