// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18326847;
  double density_weight = 0.12367053;
  double prefix_weight = 0.28424079;
  double neighborhood_weight = 0.02690346;
  double late_weight = 0.24304854;
  double critical_weight = 0.32324044;
  unsigned budget = 39;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
