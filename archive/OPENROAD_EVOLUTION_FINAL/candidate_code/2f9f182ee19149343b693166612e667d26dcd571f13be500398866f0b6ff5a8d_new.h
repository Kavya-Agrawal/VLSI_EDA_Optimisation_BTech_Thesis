// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80586361;
  double density_weight = 0.02304914;
  double prefix_weight = 0.30896566;
  double neighborhood_weight = 0.00071259;
  double late_weight = 0.26963733;
  double critical_weight = 0.42129450;
  unsigned budget = 6;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
