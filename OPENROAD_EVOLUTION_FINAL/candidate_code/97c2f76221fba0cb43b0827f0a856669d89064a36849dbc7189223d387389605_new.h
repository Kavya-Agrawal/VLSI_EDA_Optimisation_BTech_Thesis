// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40802450;
  double density_weight = 0.50003698;
  double prefix_weight = 0.23016381;
  double neighborhood_weight = 0.36486371;
  double late_weight = 0.12838391;
  double critical_weight = 0.08468546;
  unsigned budget = 16;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
