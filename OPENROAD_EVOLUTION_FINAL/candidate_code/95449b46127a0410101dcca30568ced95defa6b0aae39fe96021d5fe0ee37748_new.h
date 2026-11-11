// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20291432;
  double density_weight = 0.32823814;
  double prefix_weight = 0.12404257;
  double neighborhood_weight = 0.02633026;
  double late_weight = 0.20934779;
  double critical_weight = 0.01377853;
  unsigned budget = 29;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
