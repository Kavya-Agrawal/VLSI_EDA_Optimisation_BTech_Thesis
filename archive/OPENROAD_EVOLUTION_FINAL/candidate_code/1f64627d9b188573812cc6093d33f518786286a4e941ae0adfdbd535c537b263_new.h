// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85162591;
  double density_weight = 0.34315568;
  double prefix_weight = 0.02589105;
  double neighborhood_weight = 0.01289157;
  double late_weight = 0.12750710;
  double critical_weight = 0.48313347;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
