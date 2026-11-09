// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17452438;
  double density_weight = 0.38334514;
  double prefix_weight = 0.31056225;
  double neighborhood_weight = 0.14853771;
  double late_weight = 0.03735447;
  double critical_weight = 0.26325861;
  unsigned budget = 25;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
