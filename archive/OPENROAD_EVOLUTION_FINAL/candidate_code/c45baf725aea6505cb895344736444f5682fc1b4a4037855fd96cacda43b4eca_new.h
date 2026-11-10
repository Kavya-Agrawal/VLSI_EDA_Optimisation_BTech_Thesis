// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64547345;
  double density_weight = 0.10353387;
  double prefix_weight = 0.37004721;
  double neighborhood_weight = 0.19220721;
  double late_weight = 0.13570043;
  double critical_weight = 0.45969789;
  unsigned budget = 4;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
