// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07601650;
  double density_weight = 0.13003291;
  double prefix_weight = 0.10333428;
  double neighborhood_weight = 0.26560351;
  double late_weight = 0.03658962;
  double critical_weight = 0.30952673;
  unsigned budget = 6;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
