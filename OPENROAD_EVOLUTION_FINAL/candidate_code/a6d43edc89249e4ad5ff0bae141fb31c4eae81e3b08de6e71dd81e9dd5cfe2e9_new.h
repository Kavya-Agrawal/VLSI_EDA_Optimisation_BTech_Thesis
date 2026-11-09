// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72130538;
  double density_weight = 0.02164475;
  double prefix_weight = 0.42143806;
  double neighborhood_weight = 0.17116626;
  double late_weight = 0.18293559;
  double critical_weight = 0.15936620;
  unsigned budget = 34;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
