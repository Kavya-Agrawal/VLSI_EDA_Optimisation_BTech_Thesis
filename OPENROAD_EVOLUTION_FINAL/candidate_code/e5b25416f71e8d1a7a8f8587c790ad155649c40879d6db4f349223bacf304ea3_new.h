// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27155742;
  double density_weight = 0.53503003;
  double prefix_weight = 0.20603464;
  double neighborhood_weight = 0.11579513;
  double late_weight = 0.27143374;
  double critical_weight = 0.48452791;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
