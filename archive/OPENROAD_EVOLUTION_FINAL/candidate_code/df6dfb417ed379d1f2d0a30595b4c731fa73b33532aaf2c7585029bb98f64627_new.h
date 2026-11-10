// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83071498;
  double density_weight = 0.31301819;
  double prefix_weight = 0.40207814;
  double neighborhood_weight = 0.20391954;
  double late_weight = 0.13962014;
  double critical_weight = 0.02682960;
  unsigned budget = 5;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
