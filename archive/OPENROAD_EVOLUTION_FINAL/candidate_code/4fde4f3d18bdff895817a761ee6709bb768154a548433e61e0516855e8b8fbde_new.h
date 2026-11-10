// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15079642;
  double density_weight = 0.00876197;
  double prefix_weight = 0.45356647;
  double neighborhood_weight = 0.34955424;
  double late_weight = 0.22276122;
  double critical_weight = 0.05014361;
  unsigned budget = 5;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
