// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27554656;
  double density_weight = 0.47739039;
  double prefix_weight = 0.42600784;
  double neighborhood_weight = 0.39433790;
  double late_weight = 0.01616666;
  double critical_weight = 0.10904838;
  unsigned budget = 21;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
