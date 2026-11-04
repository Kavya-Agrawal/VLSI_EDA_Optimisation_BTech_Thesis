// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82155601;
  double density_weight = 0.38369143;
  double prefix_weight = 0.02038123;
  double neighborhood_weight = 0.35675312;
  double late_weight = 0.11709281;
  double critical_weight = 0.13571312;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
