// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13100625;
  double density_weight = 0.36916296;
  double prefix_weight = 0.10452407;
  double neighborhood_weight = 0.17522047;
  double late_weight = 0.04964335;
  double critical_weight = 0.19339542;
  unsigned budget = 39;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
