// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06575976;
  double density_weight = 0.12502311;
  double prefix_weight = 0.12453173;
  double neighborhood_weight = 0.12579569;
  double late_weight = 0.25015369;
  double critical_weight = 0.12430653;
  unsigned budget = 39;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
