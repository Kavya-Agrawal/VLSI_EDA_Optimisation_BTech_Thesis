// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13974930;
  double density_weight = 0.46987387;
  double prefix_weight = 0.26356761;
  double neighborhood_weight = 0.37654730;
  double late_weight = 0.13177436;
  double critical_weight = 0.08521970;
  unsigned budget = 29;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
