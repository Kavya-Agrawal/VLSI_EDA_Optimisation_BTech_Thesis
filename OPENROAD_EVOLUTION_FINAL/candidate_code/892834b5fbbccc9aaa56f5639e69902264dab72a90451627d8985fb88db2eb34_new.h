// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14733197;
  double density_weight = 0.34237853;
  double prefix_weight = 0.19677593;
  double neighborhood_weight = 0.28502935;
  double late_weight = 0.00816728;
  double critical_weight = 0.26751630;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
