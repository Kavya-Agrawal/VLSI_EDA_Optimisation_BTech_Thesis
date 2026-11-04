// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79995616;
  double density_weight = 0.16609223;
  double prefix_weight = 0.17690867;
  double neighborhood_weight = 0.04257079;
  double late_weight = 0.05479538;
  double critical_weight = 0.40858622;
  unsigned budget = 26;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
