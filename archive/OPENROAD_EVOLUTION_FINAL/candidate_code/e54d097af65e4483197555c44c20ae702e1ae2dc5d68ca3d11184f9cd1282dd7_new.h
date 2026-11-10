// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27726650;
  double density_weight = 0.05280361;
  double prefix_weight = 0.16824789;
  double neighborhood_weight = 0.00554219;
  double late_weight = 0.26751620;
  double critical_weight = 0.35338010;
  unsigned budget = 7;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
