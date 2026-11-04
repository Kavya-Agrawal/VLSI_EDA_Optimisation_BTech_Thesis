// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47321802;
  double density_weight = 0.19680359;
  double prefix_weight = 0.02959828;
  double neighborhood_weight = 0.33049558;
  double late_weight = 0.00303662;
  double critical_weight = 0.34516564;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
