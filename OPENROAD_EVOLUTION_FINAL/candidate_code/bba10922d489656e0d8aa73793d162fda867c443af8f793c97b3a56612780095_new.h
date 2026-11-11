// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97830936;
  double density_weight = 0.27573831;
  double prefix_weight = 0.02612272;
  double neighborhood_weight = 0.24067758;
  double late_weight = 0.19777954;
  double critical_weight = 0.31734645;
  unsigned budget = 13;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
