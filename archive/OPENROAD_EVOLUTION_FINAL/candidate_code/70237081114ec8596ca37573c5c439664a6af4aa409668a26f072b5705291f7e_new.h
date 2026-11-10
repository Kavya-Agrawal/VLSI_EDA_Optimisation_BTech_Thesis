// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35002981;
  double density_weight = 0.58201270;
  double prefix_weight = 0.42416349;
  double neighborhood_weight = 0.33809335;
  double late_weight = 0.29296193;
  double critical_weight = 0.29685257;
  unsigned budget = 4;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
