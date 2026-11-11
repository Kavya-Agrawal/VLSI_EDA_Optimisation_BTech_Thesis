// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30527904;
  double density_weight = 0.26045043;
  double prefix_weight = 0.37396871;
  double neighborhood_weight = 0.08031098;
  double late_weight = 0.05039913;
  double critical_weight = 0.32017347;
  unsigned budget = 27;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
