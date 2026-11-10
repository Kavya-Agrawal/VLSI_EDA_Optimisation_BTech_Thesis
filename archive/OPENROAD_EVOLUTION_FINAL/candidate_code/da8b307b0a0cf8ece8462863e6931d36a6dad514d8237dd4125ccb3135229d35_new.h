// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50302053;
  double density_weight = 0.39226825;
  double prefix_weight = 0.47391364;
  double neighborhood_weight = 0.09963306;
  double late_weight = 0.20455482;
  double critical_weight = 0.36758600;
  unsigned budget = 23;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
