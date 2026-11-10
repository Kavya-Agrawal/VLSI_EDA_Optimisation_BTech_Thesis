// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21329500;
  double density_weight = 0.12729820;
  double prefix_weight = 0.20128118;
  double neighborhood_weight = 0.36744162;
  double late_weight = 0.22447212;
  double critical_weight = 0.37402886;
  unsigned budget = 23;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
