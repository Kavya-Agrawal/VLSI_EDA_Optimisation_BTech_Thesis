// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26907751;
  double density_weight = 0.51328831;
  double prefix_weight = 0.23890280;
  double neighborhood_weight = 0.22999004;
  double late_weight = 0.06955585;
  double critical_weight = 0.13485088;
  unsigned budget = 37;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
