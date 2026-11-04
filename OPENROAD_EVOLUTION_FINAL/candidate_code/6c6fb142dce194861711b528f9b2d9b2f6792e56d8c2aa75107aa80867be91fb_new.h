// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96486375;
  double density_weight = 0.00698124;
  double prefix_weight = 0.44915006;
  double neighborhood_weight = 0.28704994;
  double late_weight = 0.14459685;
  double critical_weight = 0.02885210;
  unsigned budget = 28;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
