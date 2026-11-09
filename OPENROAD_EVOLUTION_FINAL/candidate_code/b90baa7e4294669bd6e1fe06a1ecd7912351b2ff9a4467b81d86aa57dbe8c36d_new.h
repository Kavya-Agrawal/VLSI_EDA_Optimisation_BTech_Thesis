// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74748202;
  double density_weight = 0.22029744;
  double prefix_weight = 0.49178325;
  double neighborhood_weight = 0.02266403;
  double late_weight = 0.20672674;
  double critical_weight = 0.05082284;
  unsigned budget = 16;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
