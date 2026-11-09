// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68249479;
  double density_weight = 0.14100428;
  double prefix_weight = 0.34403759;
  double neighborhood_weight = 0.34574690;
  double late_weight = 0.20226087;
  double critical_weight = 0.03961371;
  unsigned budget = 36;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
