// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95726767;
  double density_weight = 0.56144641;
  double prefix_weight = 0.00354833;
  double neighborhood_weight = 0.00544159;
  double late_weight = 0.14515134;
  double critical_weight = 0.06852145;
  unsigned budget = 24;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
