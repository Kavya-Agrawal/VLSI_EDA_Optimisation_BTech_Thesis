// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24694619;
  double density_weight = 0.14750303;
  double prefix_weight = 0.41190884;
  double neighborhood_weight = 0.02462461;
  double late_weight = 0.21518312;
  double critical_weight = 0.22515913;
  unsigned budget = 22;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
