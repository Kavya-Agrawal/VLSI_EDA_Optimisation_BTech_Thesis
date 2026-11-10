// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60688763;
  double density_weight = 0.15484950;
  double prefix_weight = 0.13411773;
  double neighborhood_weight = 0.02402469;
  double late_weight = 0.13131091;
  double critical_weight = 0.22480970;
  unsigned budget = 15;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
