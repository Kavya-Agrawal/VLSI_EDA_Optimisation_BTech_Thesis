// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60428455;
  double density_weight = 0.22472032;
  double prefix_weight = 0.10300614;
  double neighborhood_weight = 0.38939164;
  double late_weight = 0.18409244;
  double critical_weight = 0.48050667;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
