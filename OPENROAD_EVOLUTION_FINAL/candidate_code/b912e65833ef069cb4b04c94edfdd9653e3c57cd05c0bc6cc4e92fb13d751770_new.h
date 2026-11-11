// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29207610;
  double density_weight = 0.29189158;
  double prefix_weight = 0.35778886;
  double neighborhood_weight = 0.18068140;
  double late_weight = 0.10077804;
  double critical_weight = 0.00336743;
  unsigned budget = 12;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
