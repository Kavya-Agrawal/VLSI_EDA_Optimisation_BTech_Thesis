// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49789164;
  double density_weight = 0.03819406;
  double prefix_weight = 0.09897861;
  double neighborhood_weight = 0.27347560;
  double late_weight = 0.22141904;
  double critical_weight = 0.36907220;
  unsigned budget = 5;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
