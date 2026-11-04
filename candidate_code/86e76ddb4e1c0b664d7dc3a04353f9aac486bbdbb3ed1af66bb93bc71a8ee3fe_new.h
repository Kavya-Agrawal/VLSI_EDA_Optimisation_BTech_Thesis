// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95891268;
  double density_weight = 0.13709962;
  double prefix_weight = 0.09755815;
  double neighborhood_weight = 0.04920132;
  double late_weight = 0.19801740;
  double critical_weight = 0.15613335;
  unsigned budget = 40;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
