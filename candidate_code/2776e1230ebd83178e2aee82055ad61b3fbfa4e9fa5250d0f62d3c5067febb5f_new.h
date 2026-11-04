// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20299439;
  double density_weight = 0.13248697;
  double prefix_weight = 0.38611306;
  double neighborhood_weight = 0.14691740;
  double late_weight = 0.07228762;
  double critical_weight = 0.04634908;
  unsigned budget = 25;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
