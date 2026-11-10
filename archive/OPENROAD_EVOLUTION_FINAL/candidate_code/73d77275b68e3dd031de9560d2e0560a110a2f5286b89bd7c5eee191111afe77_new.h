// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81354447;
  double density_weight = 0.39108174;
  double prefix_weight = 0.00116397;
  double neighborhood_weight = 0.14267651;
  double late_weight = 0.15005566;
  double critical_weight = 0.27558252;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
