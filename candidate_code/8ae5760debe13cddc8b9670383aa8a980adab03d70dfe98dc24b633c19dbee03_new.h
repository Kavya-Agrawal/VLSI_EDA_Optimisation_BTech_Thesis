// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29299092;
  double density_weight = 0.39060716;
  double prefix_weight = 0.12810841;
  double neighborhood_weight = 0.34025979;
  double late_weight = 0.09483789;
  double critical_weight = 0.15893732;
  unsigned budget = 13;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
