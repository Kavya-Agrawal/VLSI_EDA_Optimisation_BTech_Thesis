// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81747785;
  double density_weight = 0.02807825;
  double prefix_weight = 0.27361788;
  double neighborhood_weight = 0.12857871;
  double late_weight = 0.17925434;
  double critical_weight = 0.07643286;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
