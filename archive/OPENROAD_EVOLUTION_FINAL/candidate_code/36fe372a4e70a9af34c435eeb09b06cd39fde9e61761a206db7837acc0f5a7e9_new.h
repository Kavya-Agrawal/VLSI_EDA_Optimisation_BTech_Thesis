// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87653789;
  double density_weight = 0.45511211;
  double prefix_weight = 0.02186130;
  double neighborhood_weight = 0.25249363;
  double late_weight = 0.26055943;
  double critical_weight = 0.43051799;
  unsigned budget = 35;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
