// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89443892;
  double density_weight = 0.07810364;
  double prefix_weight = 0.13456875;
  double neighborhood_weight = 0.17735301;
  double late_weight = 0.01538866;
  double critical_weight = 0.29878791;
  unsigned budget = 23;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
