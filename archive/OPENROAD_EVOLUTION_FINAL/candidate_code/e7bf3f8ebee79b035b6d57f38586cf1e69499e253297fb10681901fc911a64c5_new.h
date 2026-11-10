// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93360776;
  double density_weight = 0.02376571;
  double prefix_weight = 0.40531811;
  double neighborhood_weight = 0.37675138;
  double late_weight = 0.20848432;
  double critical_weight = 0.10619834;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
