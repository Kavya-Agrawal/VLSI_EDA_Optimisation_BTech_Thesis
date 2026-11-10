// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87253167;
  double density_weight = 0.13191221;
  double prefix_weight = 0.39639346;
  double neighborhood_weight = 0.05297243;
  double late_weight = 0.01920039;
  double critical_weight = 0.18110089;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
