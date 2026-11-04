// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05547748;
  double density_weight = 0.45662936;
  double prefix_weight = 0.48624696;
  double neighborhood_weight = 0.36365719;
  double late_weight = 0.08318448;
  double critical_weight = 0.36923769;
  unsigned budget = 9;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
