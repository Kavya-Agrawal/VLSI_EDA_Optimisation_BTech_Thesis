// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04639557;
  double density_weight = 0.17022402;
  double prefix_weight = 0.46561234;
  double neighborhood_weight = 0.09624403;
  double late_weight = 0.17492703;
  double critical_weight = 0.02835028;
  unsigned budget = 9;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
