// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26059223;
  double density_weight = 0.00887256;
  double prefix_weight = 0.02206250;
  double neighborhood_weight = 0.21014846;
  double late_weight = 0.23154252;
  double critical_weight = 0.28285168;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
