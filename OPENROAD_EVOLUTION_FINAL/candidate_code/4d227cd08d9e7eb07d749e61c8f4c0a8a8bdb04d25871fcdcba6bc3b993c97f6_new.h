// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97024603;
  double density_weight = 0.26129257;
  double prefix_weight = 0.23398165;
  double neighborhood_weight = 0.11122968;
  double late_weight = 0.26013717;
  double critical_weight = 0.33333165;
  unsigned budget = 32;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
