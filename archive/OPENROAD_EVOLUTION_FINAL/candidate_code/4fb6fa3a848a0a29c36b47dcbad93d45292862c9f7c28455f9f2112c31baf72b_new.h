// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61927859;
  double density_weight = 0.08460118;
  double prefix_weight = 0.18501171;
  double neighborhood_weight = 0.01643907;
  double late_weight = 0.06287065;
  double critical_weight = 0.46753580;
  unsigned budget = 24;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
