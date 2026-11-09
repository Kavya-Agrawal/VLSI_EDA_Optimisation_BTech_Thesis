// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41557985;
  double density_weight = 0.35643723;
  double prefix_weight = 0.41775876;
  double neighborhood_weight = 0.02135296;
  double late_weight = 0.07902435;
  double critical_weight = 0.40234969;
  unsigned budget = 14;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
