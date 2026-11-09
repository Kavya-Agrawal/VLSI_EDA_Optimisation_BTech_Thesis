// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55156333;
  double density_weight = 0.02251002;
  double prefix_weight = 0.11226325;
  double neighborhood_weight = 0.28504399;
  double late_weight = 0.17710084;
  double critical_weight = 0.03684775;
  unsigned budget = 11;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
