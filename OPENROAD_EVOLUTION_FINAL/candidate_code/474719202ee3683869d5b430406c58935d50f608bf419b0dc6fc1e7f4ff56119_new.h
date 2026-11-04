// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54329111;
  double density_weight = 0.17095738;
  double prefix_weight = 0.30370808;
  double neighborhood_weight = 0.37342528;
  double late_weight = 0.21276245;
  double critical_weight = 0.04622468;
  unsigned budget = 16;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
