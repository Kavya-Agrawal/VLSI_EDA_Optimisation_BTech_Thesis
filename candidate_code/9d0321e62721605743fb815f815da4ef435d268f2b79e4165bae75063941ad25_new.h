// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61775182;
  double density_weight = 0.19134405;
  double prefix_weight = 0.27261578;
  double neighborhood_weight = 0.03268725;
  double late_weight = 0.04176976;
  double critical_weight = 0.05714028;
  unsigned budget = 10;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
