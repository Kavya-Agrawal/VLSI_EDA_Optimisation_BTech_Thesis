// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49069855;
  double density_weight = 0.57009901;
  double prefix_weight = 0.15489664;
  double neighborhood_weight = 0.30675951;
  double late_weight = 0.05111157;
  double critical_weight = 0.12044470;
  unsigned budget = 14;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
