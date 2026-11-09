// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53961410;
  double density_weight = 0.45595134;
  double prefix_weight = 0.48008757;
  double neighborhood_weight = 0.10886446;
  double late_weight = 0.15719454;
  double critical_weight = 0.03599102;
  unsigned budget = 20;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
