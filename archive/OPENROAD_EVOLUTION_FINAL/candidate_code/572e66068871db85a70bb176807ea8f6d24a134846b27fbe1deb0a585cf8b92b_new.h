// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43167810;
  double density_weight = 0.52213148;
  double prefix_weight = 0.47995420;
  double neighborhood_weight = 0.39694641;
  double late_weight = 0.18144232;
  double critical_weight = 0.20259526;
  unsigned budget = 8;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
