// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30839247;
  double density_weight = 0.01081058;
  double prefix_weight = 0.41677155;
  double neighborhood_weight = 0.11730179;
  double late_weight = 0.00122444;
  double critical_weight = 0.36844436;
  unsigned budget = 6;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
