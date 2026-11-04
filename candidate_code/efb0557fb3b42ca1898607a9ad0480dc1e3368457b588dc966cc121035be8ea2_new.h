// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59652596;
  double density_weight = 0.53403055;
  double prefix_weight = 0.00032199;
  double neighborhood_weight = 0.05457654;
  double late_weight = 0.06560917;
  double critical_weight = 0.14647986;
  unsigned budget = 18;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
