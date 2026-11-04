// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90224671;
  double density_weight = 0.45944670;
  double prefix_weight = 0.08869035;
  double neighborhood_weight = 0.08912311;
  double late_weight = 0.21771982;
  double critical_weight = 0.13164160;
  unsigned budget = 37;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
