// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85782403;
  double density_weight = 0.52297712;
  double prefix_weight = 0.45216378;
  double neighborhood_weight = 0.31062518;
  double late_weight = 0.17668099;
  double critical_weight = 0.02395133;
  unsigned budget = 33;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
