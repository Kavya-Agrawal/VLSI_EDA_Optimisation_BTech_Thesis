// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87130706;
  double density_weight = 0.18794960;
  double prefix_weight = 0.18816519;
  double neighborhood_weight = 0.33955950;
  double late_weight = 0.28533871;
  double critical_weight = 0.13273739;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
