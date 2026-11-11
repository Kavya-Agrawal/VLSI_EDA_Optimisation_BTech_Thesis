// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97667534;
  double density_weight = 0.11120010;
  double prefix_weight = 0.22401945;
  double neighborhood_weight = 0.07678713;
  double late_weight = 0.11639267;
  double critical_weight = 0.04186897;
  unsigned budget = 13;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
