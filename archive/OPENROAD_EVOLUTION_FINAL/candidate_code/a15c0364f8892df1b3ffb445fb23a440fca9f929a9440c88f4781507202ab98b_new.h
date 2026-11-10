// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47376984;
  double density_weight = 0.55570821;
  double prefix_weight = 0.41186270;
  double neighborhood_weight = 0.25384914;
  double late_weight = 0.26069380;
  double critical_weight = 0.01500069;
  unsigned budget = 9;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
