// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07745592;
  double density_weight = 0.32025294;
  double prefix_weight = 0.08388621;
  double neighborhood_weight = 0.28482237;
  double late_weight = 0.03890105;
  double critical_weight = 0.10117821;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
