// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12516102;
  double density_weight = 0.29461112;
  double prefix_weight = 0.08074185;
  double neighborhood_weight = 0.20088037;
  double late_weight = 0.18123776;
  double critical_weight = 0.32625158;
  unsigned budget = 22;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
