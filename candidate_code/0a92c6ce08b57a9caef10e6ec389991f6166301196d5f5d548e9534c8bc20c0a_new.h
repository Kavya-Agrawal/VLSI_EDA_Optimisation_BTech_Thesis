// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37141359;
  double density_weight = 0.54348624;
  double prefix_weight = 0.18298315;
  double neighborhood_weight = 0.23969748;
  double late_weight = 0.14956750;
  double critical_weight = 0.31299514;
  unsigned budget = 21;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
