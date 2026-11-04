// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54005977;
  double density_weight = 0.15534513;
  double prefix_weight = 0.32836123;
  double neighborhood_weight = 0.13374469;
  double late_weight = 0.08326632;
  double critical_weight = 0.35774358;
  unsigned budget = 21;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
