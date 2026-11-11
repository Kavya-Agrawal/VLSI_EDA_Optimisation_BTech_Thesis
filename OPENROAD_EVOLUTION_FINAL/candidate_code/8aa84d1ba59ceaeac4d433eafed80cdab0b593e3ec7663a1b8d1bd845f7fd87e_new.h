// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63318824;
  double density_weight = 0.46469462;
  double prefix_weight = 0.19678711;
  double neighborhood_weight = 0.39112113;
  double late_weight = 0.00120001;
  double critical_weight = 0.06636345;
  unsigned budget = 36;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
