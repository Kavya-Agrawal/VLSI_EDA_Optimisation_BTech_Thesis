// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24871389;
  double density_weight = 0.14829863;
  double prefix_weight = 0.30477077;
  double neighborhood_weight = 0.07621077;
  double late_weight = 0.03981327;
  double critical_weight = 0.17159296;
  unsigned budget = 22;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
