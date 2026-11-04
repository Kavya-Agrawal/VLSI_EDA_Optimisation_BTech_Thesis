// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76160021;
  double density_weight = 0.14487241;
  double prefix_weight = 0.32987552;
  double neighborhood_weight = 0.13388336;
  double late_weight = 0.28251711;
  double critical_weight = 0.18248469;
  unsigned budget = 33;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
