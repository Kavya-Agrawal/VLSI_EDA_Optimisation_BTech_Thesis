// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85859486;
  double density_weight = 0.42317495;
  double prefix_weight = 0.31231979;
  double neighborhood_weight = 0.00153199;
  double late_weight = 0.22879367;
  double critical_weight = 0.47401553;
  unsigned budget = 36;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
