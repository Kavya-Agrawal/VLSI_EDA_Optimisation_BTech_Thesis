// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58762136;
  double density_weight = 0.21367472;
  double prefix_weight = 0.10689084;
  double neighborhood_weight = 0.04408643;
  double late_weight = 0.25833636;
  double critical_weight = 0.08400961;
  unsigned budget = 9;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
