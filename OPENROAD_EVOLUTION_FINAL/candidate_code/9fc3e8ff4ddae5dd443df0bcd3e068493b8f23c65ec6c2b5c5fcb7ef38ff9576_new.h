// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59950767;
  double density_weight = 0.47377249;
  double prefix_weight = 0.08949289;
  double neighborhood_weight = 0.30198784;
  double late_weight = 0.22654016;
  double critical_weight = 0.20808219;
  unsigned budget = 8;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
