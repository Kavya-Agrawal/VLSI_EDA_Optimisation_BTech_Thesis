// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44531787;
  double density_weight = 0.41376795;
  double prefix_weight = 0.35995403;
  double neighborhood_weight = 0.10324103;
  double late_weight = 0.23969950;
  double critical_weight = 0.13224308;
  unsigned budget = 11;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
