// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77779004;
  double density_weight = 0.50457966;
  double prefix_weight = 0.29558870;
  double neighborhood_weight = 0.07493742;
  double late_weight = 0.01370881;
  double critical_weight = 0.07399709;
  unsigned budget = 19;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
