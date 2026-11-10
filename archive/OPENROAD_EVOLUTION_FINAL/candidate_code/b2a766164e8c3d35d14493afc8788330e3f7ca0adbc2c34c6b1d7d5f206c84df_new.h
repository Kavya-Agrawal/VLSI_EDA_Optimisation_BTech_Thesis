// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27299214;
  double density_weight = 0.31005986;
  double prefix_weight = 0.39752560;
  double neighborhood_weight = 0.30611697;
  double late_weight = 0.11108221;
  double critical_weight = 0.16856206;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
