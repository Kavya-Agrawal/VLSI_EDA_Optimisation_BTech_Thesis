// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88767322;
  double density_weight = 0.31672444;
  double prefix_weight = 0.27644720;
  double neighborhood_weight = 0.09489279;
  double late_weight = 0.01790933;
  double critical_weight = 0.05083888;
  unsigned budget = 37;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
