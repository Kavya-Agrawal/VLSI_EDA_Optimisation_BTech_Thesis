// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28189420;
  double density_weight = 0.38950610;
  double prefix_weight = 0.15472685;
  double neighborhood_weight = 0.19163407;
  double late_weight = 0.01578854;
  double critical_weight = 0.11133367;
  unsigned budget = 32;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
