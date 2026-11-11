// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75236041;
  double density_weight = 0.34870196;
  double prefix_weight = 0.29864682;
  double neighborhood_weight = 0.22317417;
  double late_weight = 0.23671038;
  double critical_weight = 0.14191750;
  unsigned budget = 10;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
