// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72244072;
  double density_weight = 0.48484313;
  double prefix_weight = 0.49485669;
  double neighborhood_weight = 0.22361364;
  double late_weight = 0.15045376;
  double critical_weight = 0.25810395;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
