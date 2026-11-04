// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25118144;
  double density_weight = 0.13627043;
  double prefix_weight = 0.12158603;
  double neighborhood_weight = 0.14772780;
  double late_weight = 0.00564543;
  double critical_weight = 0.05023765;
  unsigned budget = 4;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
