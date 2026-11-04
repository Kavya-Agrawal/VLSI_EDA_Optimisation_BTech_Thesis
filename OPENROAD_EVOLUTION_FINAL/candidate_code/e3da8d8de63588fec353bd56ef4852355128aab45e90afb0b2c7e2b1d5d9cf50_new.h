// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50623417;
  double density_weight = 0.36579865;
  double prefix_weight = 0.19540441;
  double neighborhood_weight = 0.00259547;
  double late_weight = 0.07818525;
  double critical_weight = 0.34487212;
  unsigned budget = 40;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
