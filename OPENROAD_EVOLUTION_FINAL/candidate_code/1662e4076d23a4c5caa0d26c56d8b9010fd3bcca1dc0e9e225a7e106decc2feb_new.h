// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56392191;
  double density_weight = 0.47314731;
  double prefix_weight = 0.10413614;
  double neighborhood_weight = 0.07107727;
  double late_weight = 0.23509810;
  double critical_weight = 0.49838428;
  unsigned budget = 21;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
