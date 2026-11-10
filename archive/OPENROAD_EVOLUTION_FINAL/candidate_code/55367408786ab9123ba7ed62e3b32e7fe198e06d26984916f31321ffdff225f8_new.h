// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68129850;
  double density_weight = 0.22019949;
  double prefix_weight = 0.20296726;
  double neighborhood_weight = 0.00069607;
  double late_weight = 0.22647550;
  double critical_weight = 0.17547796;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
