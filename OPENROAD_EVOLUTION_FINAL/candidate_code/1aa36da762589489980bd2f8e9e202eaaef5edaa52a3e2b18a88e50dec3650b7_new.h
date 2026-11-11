// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66185802;
  double density_weight = 0.29022246;
  double prefix_weight = 0.01597276;
  double neighborhood_weight = 0.21015621;
  double late_weight = 0.00241195;
  double critical_weight = 0.36208317;
  unsigned budget = 13;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
