// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23110391;
  double density_weight = 0.23425112;
  double prefix_weight = 0.15183153;
  double neighborhood_weight = 0.18301877;
  double late_weight = 0.17723259;
  double critical_weight = 0.49614574;
  unsigned budget = 5;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
