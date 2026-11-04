// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67174840;
  double density_weight = 0.26545851;
  double prefix_weight = 0.10208834;
  double neighborhood_weight = 0.02513283;
  double late_weight = 0.24175078;
  double critical_weight = 0.30885786;
  unsigned budget = 7;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
