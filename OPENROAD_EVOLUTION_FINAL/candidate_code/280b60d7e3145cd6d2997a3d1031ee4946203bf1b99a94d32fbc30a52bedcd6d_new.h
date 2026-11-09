// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67749451;
  double density_weight = 0.24816470;
  double prefix_weight = 0.15271337;
  double neighborhood_weight = 0.27041561;
  double late_weight = 0.25843288;
  double critical_weight = 0.35891482;
  unsigned budget = 35;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
