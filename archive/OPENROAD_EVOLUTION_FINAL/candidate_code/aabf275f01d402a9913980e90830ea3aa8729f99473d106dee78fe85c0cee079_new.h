// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98172559;
  double density_weight = 0.01602276;
  double prefix_weight = 0.23688664;
  double neighborhood_weight = 0.24854417;
  double late_weight = 0.19114972;
  double critical_weight = 0.37066413;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
