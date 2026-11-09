// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25211534;
  double density_weight = 0.03794170;
  double prefix_weight = 0.40569155;
  double neighborhood_weight = 0.16648899;
  double late_weight = 0.18489596;
  double critical_weight = 0.00428784;
  unsigned budget = 23;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
