// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24757186;
  double density_weight = 0.14897548;
  double prefix_weight = 0.42216590;
  double neighborhood_weight = 0.00247517;
  double late_weight = 0.02646074;
  double critical_weight = 0.21157978;
  unsigned budget = 38;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
