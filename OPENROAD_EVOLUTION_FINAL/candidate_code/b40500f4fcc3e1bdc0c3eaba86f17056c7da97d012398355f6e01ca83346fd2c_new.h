// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37657870;
  double density_weight = 0.36076349;
  double prefix_weight = 0.21995971;
  double neighborhood_weight = 0.38649469;
  double late_weight = 0.11589853;
  double critical_weight = 0.27894966;
  unsigned budget = 31;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
