// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23765522;
  double density_weight = 0.46359685;
  double prefix_weight = 0.00732474;
  double neighborhood_weight = 0.00175103;
  double late_weight = 0.02577306;
  double critical_weight = 0.30755619;
  unsigned budget = 6;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
