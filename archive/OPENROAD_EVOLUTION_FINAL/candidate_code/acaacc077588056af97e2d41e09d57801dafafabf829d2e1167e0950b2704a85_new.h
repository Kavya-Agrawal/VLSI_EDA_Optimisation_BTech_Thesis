// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25524030;
  double density_weight = 0.22106582;
  double prefix_weight = 0.44713225;
  double neighborhood_weight = 0.02283629;
  double late_weight = 0.24350116;
  double critical_weight = 0.41822271;
  unsigned budget = 30;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
