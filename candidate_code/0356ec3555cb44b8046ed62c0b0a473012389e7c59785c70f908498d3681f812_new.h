// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63400231;
  double density_weight = 0.43326248;
  double prefix_weight = 0.22294890;
  double neighborhood_weight = 0.31817080;
  double late_weight = 0.06299058;
  double critical_weight = 0.38157279;
  unsigned budget = 13;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
