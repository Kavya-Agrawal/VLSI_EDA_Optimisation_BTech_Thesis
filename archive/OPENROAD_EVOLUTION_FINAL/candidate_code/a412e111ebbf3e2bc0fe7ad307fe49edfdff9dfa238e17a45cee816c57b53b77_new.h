// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02180773;
  double density_weight = 0.51470591;
  double prefix_weight = 0.20989751;
  double neighborhood_weight = 0.32531017;
  double late_weight = 0.13649623;
  double critical_weight = 0.47027333;
  unsigned budget = 31;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
