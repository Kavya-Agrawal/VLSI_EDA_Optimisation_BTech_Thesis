// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45610194;
  double density_weight = 0.55520628;
  double prefix_weight = 0.04716166;
  double neighborhood_weight = 0.24874690;
  double late_weight = 0.14426646;
  double critical_weight = 0.19907468;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
