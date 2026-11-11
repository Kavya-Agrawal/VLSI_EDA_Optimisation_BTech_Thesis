// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08595262;
  double density_weight = 0.41978752;
  double prefix_weight = 0.29529390;
  double neighborhood_weight = 0.28683069;
  double late_weight = 0.22275086;
  double critical_weight = 0.00852468;
  unsigned budget = 24;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
