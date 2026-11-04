// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32393151;
  double density_weight = 0.00798555;
  double prefix_weight = 0.42248416;
  double neighborhood_weight = 0.04744808;
  double late_weight = 0.00767047;
  double critical_weight = 0.39064511;
  unsigned budget = 32;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
