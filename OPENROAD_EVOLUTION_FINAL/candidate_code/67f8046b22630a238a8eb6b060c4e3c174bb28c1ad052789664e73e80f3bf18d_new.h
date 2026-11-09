// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21608273;
  double density_weight = 0.37240106;
  double prefix_weight = 0.48277761;
  double neighborhood_weight = 0.30707573;
  double late_weight = 0.29499982;
  double critical_weight = 0.44990182;
  unsigned budget = 35;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
