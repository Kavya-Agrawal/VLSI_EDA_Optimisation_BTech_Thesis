// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36184388;
  double density_weight = 0.17296171;
  double prefix_weight = 0.28027975;
  double neighborhood_weight = 0.10274370;
  double late_weight = 0.05572224;
  double critical_weight = 0.28684389;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
