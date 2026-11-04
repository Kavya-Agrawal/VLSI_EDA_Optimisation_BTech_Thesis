// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65358596;
  double density_weight = 0.02831668;
  double prefix_weight = 0.37203846;
  double neighborhood_weight = 0.01458916;
  double late_weight = 0.25693277;
  double critical_weight = 0.07614108;
  unsigned budget = 17;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
