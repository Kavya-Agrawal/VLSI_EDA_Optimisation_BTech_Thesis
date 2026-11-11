// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63908319;
  double density_weight = 0.34247277;
  double prefix_weight = 0.32960339;
  double neighborhood_weight = 0.10314786;
  double late_weight = 0.19466634;
  double critical_weight = 0.12334534;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
