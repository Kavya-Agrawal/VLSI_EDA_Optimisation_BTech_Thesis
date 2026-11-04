// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77843698;
  double density_weight = 0.53122966;
  double prefix_weight = 0.24536491;
  double neighborhood_weight = 0.13616955;
  double late_weight = 0.24298598;
  double critical_weight = 0.22163211;
  unsigned budget = 33;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
