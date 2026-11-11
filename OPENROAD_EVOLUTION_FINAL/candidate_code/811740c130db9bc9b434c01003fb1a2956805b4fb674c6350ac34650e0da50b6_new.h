// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24300559;
  double density_weight = 0.00907870;
  double prefix_weight = 0.22950419;
  double neighborhood_weight = 0.02609595;
  double late_weight = 0.14944713;
  double critical_weight = 0.03779587;
  unsigned budget = 13;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
