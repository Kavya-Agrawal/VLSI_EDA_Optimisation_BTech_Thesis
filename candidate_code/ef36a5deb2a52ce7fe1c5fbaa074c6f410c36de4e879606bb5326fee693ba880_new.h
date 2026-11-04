// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61351560;
  double density_weight = 0.46814272;
  double prefix_weight = 0.46581240;
  double neighborhood_weight = 0.26888455;
  double late_weight = 0.15718249;
  double critical_weight = 0.30745149;
  unsigned budget = 22;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
