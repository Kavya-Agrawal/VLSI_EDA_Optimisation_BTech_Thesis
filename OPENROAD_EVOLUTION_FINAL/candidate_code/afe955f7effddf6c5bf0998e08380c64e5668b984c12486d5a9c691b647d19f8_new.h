// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47813501;
  double density_weight = 0.22522683;
  double prefix_weight = 0.11417137;
  double neighborhood_weight = 0.09978078;
  double late_weight = 0.21588931;
  double critical_weight = 0.24199010;
  unsigned budget = 27;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
