// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60543336;
  double density_weight = 0.34419381;
  double prefix_weight = 0.01149093;
  double neighborhood_weight = 0.04787523;
  double late_weight = 0.25077583;
  double critical_weight = 0.34438822;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
