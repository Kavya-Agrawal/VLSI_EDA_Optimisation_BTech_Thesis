// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93655367;
  double density_weight = 0.38345546;
  double prefix_weight = 0.09001191;
  double neighborhood_weight = 0.06121868;
  double late_weight = 0.10604811;
  double critical_weight = 0.17032132;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
