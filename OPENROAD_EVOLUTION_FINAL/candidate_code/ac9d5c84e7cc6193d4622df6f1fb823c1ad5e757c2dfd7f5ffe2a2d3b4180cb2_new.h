// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22542726;
  double density_weight = 0.24704068;
  double prefix_weight = 0.34693156;
  double neighborhood_weight = 0.28965248;
  double late_weight = 0.11331463;
  double critical_weight = 0.07267886;
  unsigned budget = 28;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
