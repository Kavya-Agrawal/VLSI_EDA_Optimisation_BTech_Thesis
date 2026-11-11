// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83573648;
  double density_weight = 0.20402971;
  double prefix_weight = 0.29868066;
  double neighborhood_weight = 0.10934262;
  double late_weight = 0.24295774;
  double critical_weight = 0.37399892;
  unsigned budget = 37;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
