// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83642083;
  double density_weight = 0.23384055;
  double prefix_weight = 0.33907095;
  double neighborhood_weight = 0.06634389;
  double late_weight = 0.13323349;
  double critical_weight = 0.30957720;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
