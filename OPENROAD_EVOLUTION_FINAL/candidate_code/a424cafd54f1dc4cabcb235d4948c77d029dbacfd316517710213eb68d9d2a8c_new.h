// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64467703;
  double density_weight = 0.21717027;
  double prefix_weight = 0.33326736;
  double neighborhood_weight = 0.23216653;
  double late_weight = 0.02789783;
  double critical_weight = 0.09861239;
  unsigned budget = 28;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
