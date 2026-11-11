// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83831603;
  double density_weight = 0.47194950;
  double prefix_weight = 0.36276407;
  double neighborhood_weight = 0.34378369;
  double late_weight = 0.23492907;
  double critical_weight = 0.44606394;
  unsigned budget = 15;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
