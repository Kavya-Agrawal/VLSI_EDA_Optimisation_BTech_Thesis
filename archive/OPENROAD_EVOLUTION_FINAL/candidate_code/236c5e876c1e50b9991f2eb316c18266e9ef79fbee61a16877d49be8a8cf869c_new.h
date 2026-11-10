// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83035049;
  double density_weight = 0.58719753;
  double prefix_weight = 0.05401507;
  double neighborhood_weight = 0.23204347;
  double late_weight = 0.08051224;
  double critical_weight = 0.34161657;
  unsigned budget = 9;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
