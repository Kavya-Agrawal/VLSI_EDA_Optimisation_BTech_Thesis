// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96861384;
  double density_weight = 0.30651345;
  double prefix_weight = 0.33769480;
  double neighborhood_weight = 0.38191356;
  double late_weight = 0.20317995;
  double critical_weight = 0.05063024;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
