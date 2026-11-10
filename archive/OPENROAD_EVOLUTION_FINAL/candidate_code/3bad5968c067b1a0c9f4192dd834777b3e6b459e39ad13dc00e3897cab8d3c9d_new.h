// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39935127;
  double density_weight = 0.50557024;
  double prefix_weight = 0.12526686;
  double neighborhood_weight = 0.17811233;
  double late_weight = 0.09180549;
  double critical_weight = 0.35242285;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
