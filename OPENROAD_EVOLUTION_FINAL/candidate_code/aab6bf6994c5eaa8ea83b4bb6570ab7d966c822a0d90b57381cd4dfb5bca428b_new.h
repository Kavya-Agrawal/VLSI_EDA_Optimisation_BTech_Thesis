// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00441433;
  double density_weight = 0.48609193;
  double prefix_weight = 0.03852944;
  double neighborhood_weight = 0.23544313;
  double late_weight = 0.17259052;
  double critical_weight = 0.07164131;
  unsigned budget = 24;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
