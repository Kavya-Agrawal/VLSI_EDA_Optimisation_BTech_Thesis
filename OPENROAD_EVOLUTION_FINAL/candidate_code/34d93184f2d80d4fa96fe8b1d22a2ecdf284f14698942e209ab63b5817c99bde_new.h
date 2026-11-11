// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41171165;
  double density_weight = 0.52587210;
  double prefix_weight = 0.05653325;
  double neighborhood_weight = 0.09706482;
  double late_weight = 0.27062474;
  double critical_weight = 0.27880802;
  unsigned budget = 30;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
