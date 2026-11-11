// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53271589;
  double density_weight = 0.00203136;
  double prefix_weight = 0.12433323;
  double neighborhood_weight = 0.22721604;
  double late_weight = 0.00797882;
  double critical_weight = 0.02077127;
  unsigned budget = 17;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
