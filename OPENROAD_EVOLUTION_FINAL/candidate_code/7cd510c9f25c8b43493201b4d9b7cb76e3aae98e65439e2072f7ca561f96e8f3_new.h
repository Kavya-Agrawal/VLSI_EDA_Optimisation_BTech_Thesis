// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25940655;
  double density_weight = 0.49121770;
  double prefix_weight = 0.49598724;
  double neighborhood_weight = 0.37036128;
  double late_weight = 0.07934897;
  double critical_weight = 0.40410124;
  unsigned budget = 38;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
