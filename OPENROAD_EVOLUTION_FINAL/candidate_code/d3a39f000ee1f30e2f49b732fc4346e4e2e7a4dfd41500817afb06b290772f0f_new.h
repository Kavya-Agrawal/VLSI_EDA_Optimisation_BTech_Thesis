// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92290686;
  double density_weight = 0.53995085;
  double prefix_weight = 0.46337338;
  double neighborhood_weight = 0.03231317;
  double late_weight = 0.27862631;
  double critical_weight = 0.45072431;
  unsigned budget = 36;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
