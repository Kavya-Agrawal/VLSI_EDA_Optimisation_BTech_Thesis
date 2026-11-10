// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36984074;
  double density_weight = 0.26902042;
  double prefix_weight = 0.39918196;
  double neighborhood_weight = 0.13003845;
  double late_weight = 0.14448898;
  double critical_weight = 0.25225674;
  unsigned budget = 25;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
