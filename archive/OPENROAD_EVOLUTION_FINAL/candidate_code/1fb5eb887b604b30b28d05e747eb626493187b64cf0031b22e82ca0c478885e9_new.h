// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94865135;
  double density_weight = 0.04483761;
  double prefix_weight = 0.13809008;
  double neighborhood_weight = 0.37524383;
  double late_weight = 0.27372461;
  double critical_weight = 0.22629251;
  unsigned budget = 24;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
