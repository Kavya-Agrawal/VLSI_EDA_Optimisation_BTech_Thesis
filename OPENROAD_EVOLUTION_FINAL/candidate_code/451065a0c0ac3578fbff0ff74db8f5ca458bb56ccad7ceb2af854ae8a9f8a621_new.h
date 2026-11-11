// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30845129;
  double density_weight = 0.39208017;
  double prefix_weight = 0.44583648;
  double neighborhood_weight = 0.32581929;
  double late_weight = 0.10788100;
  double critical_weight = 0.15708544;
  unsigned budget = 34;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
