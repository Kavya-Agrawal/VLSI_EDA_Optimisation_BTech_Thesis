// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51217210;
  double density_weight = 0.22081488;
  double prefix_weight = 0.25446272;
  double neighborhood_weight = 0.37089951;
  double late_weight = 0.23416987;
  double critical_weight = 0.34029428;
  unsigned budget = 30;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
