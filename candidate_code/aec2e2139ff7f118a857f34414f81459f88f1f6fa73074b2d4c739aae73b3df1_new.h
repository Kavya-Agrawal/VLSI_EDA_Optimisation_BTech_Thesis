// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47501582;
  double density_weight = 0.17613357;
  double prefix_weight = 0.47183744;
  double neighborhood_weight = 0.14991220;
  double late_weight = 0.06459689;
  double critical_weight = 0.46582750;
  unsigned budget = 30;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
