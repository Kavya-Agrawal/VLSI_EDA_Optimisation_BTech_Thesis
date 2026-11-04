// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78006715;
  double density_weight = 0.29392025;
  double prefix_weight = 0.45305463;
  double neighborhood_weight = 0.38153077;
  double late_weight = 0.11626555;
  double critical_weight = 0.41918614;
  unsigned budget = 17;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
