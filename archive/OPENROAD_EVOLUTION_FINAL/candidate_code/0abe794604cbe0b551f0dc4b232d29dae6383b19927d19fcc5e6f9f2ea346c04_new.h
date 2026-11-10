// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62665703;
  double density_weight = 0.53197862;
  double prefix_weight = 0.10387501;
  double neighborhood_weight = 0.18848993;
  double late_weight = 0.24850072;
  double critical_weight = 0.17157159;
  unsigned budget = 19;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
