// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02511893;
  double density_weight = 0.33424314;
  double prefix_weight = 0.27036157;
  double neighborhood_weight = 0.26330282;
  double late_weight = 0.09960815;
  double critical_weight = 0.10416237;
  unsigned budget = 39;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
