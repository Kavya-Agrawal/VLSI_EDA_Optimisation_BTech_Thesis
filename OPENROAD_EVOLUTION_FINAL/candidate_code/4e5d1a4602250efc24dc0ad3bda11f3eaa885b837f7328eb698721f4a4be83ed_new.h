// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67597410;
  double density_weight = 0.04862413;
  double prefix_weight = 0.09592032;
  double neighborhood_weight = 0.32546242;
  double late_weight = 0.23415237;
  double critical_weight = 0.08829352;
  unsigned budget = 32;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
