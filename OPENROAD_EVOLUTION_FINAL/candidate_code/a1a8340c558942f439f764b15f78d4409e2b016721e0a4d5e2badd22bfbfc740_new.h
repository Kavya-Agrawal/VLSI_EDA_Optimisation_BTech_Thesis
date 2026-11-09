// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55012869;
  double density_weight = 0.49585957;
  double prefix_weight = 0.25501019;
  double neighborhood_weight = 0.27454589;
  double late_weight = 0.16628362;
  double critical_weight = 0.02981779;
  unsigned budget = 37;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
