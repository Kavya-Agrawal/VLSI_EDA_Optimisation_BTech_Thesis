// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92693551;
  double density_weight = 0.55546544;
  double prefix_weight = 0.43583438;
  double neighborhood_weight = 0.09296403;
  double late_weight = 0.04126477;
  double critical_weight = 0.38751049;
  unsigned budget = 21;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
