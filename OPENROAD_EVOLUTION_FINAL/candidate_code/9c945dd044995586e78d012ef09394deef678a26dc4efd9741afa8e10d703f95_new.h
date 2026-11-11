// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67729980;
  double density_weight = 0.24225379;
  double prefix_weight = 0.17950896;
  double neighborhood_weight = 0.35210336;
  double late_weight = 0.24595010;
  double critical_weight = 0.28636737;
  unsigned budget = 26;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
