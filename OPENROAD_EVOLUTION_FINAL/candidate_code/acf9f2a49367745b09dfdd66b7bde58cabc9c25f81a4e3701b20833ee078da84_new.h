// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36438375;
  double density_weight = 0.59420011;
  double prefix_weight = 0.17403434;
  double neighborhood_weight = 0.14568902;
  double late_weight = 0.14852512;
  double critical_weight = 0.24902656;
  unsigned budget = 19;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
