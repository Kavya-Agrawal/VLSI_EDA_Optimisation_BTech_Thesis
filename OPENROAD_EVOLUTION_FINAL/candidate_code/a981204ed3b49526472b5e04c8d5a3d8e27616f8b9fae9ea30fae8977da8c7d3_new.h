// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09521768;
  double density_weight = 0.03536195;
  double prefix_weight = 0.22308224;
  double neighborhood_weight = 0.13630130;
  double late_weight = 0.20954079;
  double critical_weight = 0.08247364;
  unsigned budget = 37;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
