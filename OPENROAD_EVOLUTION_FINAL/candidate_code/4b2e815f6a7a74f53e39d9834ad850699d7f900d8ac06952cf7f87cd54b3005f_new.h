// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50814347;
  double density_weight = 0.45833384;
  double prefix_weight = 0.45044233;
  double neighborhood_weight = 0.19644219;
  double late_weight = 0.19304948;
  double critical_weight = 0.44672752;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
