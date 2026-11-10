// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10513285;
  double density_weight = 0.33426430;
  double prefix_weight = 0.28440517;
  double neighborhood_weight = 0.19764832;
  double late_weight = 0.22782712;
  double critical_weight = 0.18491372;
  unsigned budget = 6;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
