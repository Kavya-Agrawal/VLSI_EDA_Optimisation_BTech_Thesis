// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48238470;
  double density_weight = 0.02741734;
  double prefix_weight = 0.26532450;
  double neighborhood_weight = 0.07707155;
  double late_weight = 0.11965456;
  double critical_weight = 0.01592655;
  unsigned budget = 8;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
