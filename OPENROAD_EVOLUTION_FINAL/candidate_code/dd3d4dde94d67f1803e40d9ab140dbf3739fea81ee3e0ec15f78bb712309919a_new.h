// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23365395;
  double density_weight = 0.56355773;
  double prefix_weight = 0.03652322;
  double neighborhood_weight = 0.23968544;
  double late_weight = 0.18627066;
  double critical_weight = 0.35835824;
  unsigned budget = 22;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
