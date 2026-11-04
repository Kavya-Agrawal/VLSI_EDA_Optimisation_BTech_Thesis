// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84350344;
  double density_weight = 0.09925235;
  double prefix_weight = 0.39775298;
  double neighborhood_weight = 0.03685292;
  double late_weight = 0.02942633;
  double critical_weight = 0.02089439;
  unsigned budget = 26;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
