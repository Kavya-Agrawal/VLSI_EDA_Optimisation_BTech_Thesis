// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24632691;
  double density_weight = 0.20330073;
  double prefix_weight = 0.01653544;
  double neighborhood_weight = 0.21480828;
  double late_weight = 0.01621141;
  double critical_weight = 0.47748798;
  unsigned budget = 30;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
