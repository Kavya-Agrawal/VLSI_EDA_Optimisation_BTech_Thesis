// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58992863;
  double density_weight = 0.24382488;
  double prefix_weight = 0.24107525;
  double neighborhood_weight = 0.22485104;
  double late_weight = 0.14554471;
  double critical_weight = 0.49171322;
  unsigned budget = 10;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
