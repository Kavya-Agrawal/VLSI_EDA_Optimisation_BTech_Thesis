// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05498750;
  double density_weight = 0.51198243;
  double prefix_weight = 0.24793599;
  double neighborhood_weight = 0.34542738;
  double late_weight = 0.20913886;
  double critical_weight = 0.29857408;
  unsigned budget = 28;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
