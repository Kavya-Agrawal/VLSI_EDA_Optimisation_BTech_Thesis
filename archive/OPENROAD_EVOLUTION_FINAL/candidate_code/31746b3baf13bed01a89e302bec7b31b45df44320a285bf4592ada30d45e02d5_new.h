// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11265812;
  double density_weight = 0.09348480;
  double prefix_weight = 0.35555669;
  double neighborhood_weight = 0.00847280;
  double late_weight = 0.08772011;
  double critical_weight = 0.40275531;
  unsigned budget = 36;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
