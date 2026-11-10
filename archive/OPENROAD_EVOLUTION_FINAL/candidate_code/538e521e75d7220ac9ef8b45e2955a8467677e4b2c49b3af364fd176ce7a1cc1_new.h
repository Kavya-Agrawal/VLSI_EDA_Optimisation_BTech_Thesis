// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57686149;
  double density_weight = 0.19005959;
  double prefix_weight = 0.34147855;
  double neighborhood_weight = 0.14261137;
  double late_weight = 0.18662449;
  double critical_weight = 0.02779881;
  unsigned budget = 28;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
