// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13451621;
  double density_weight = 0.02465892;
  double prefix_weight = 0.07896290;
  double neighborhood_weight = 0.23741319;
  double late_weight = 0.01815996;
  double critical_weight = 0.04724891;
  unsigned budget = 11;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
