// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61120541;
  double density_weight = 0.36842561;
  double prefix_weight = 0.16221564;
  double neighborhood_weight = 0.02528272;
  double late_weight = 0.18107583;
  double critical_weight = 0.22565141;
  unsigned budget = 6;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
