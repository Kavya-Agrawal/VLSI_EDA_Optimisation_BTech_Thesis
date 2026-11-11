// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71759711;
  double density_weight = 0.19982111;
  double prefix_weight = 0.05405902;
  double neighborhood_weight = 0.22702405;
  double late_weight = 0.10040384;
  double critical_weight = 0.33865272;
  unsigned budget = 14;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
