// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25110388;
  double density_weight = 0.55640215;
  double prefix_weight = 0.15029454;
  double neighborhood_weight = 0.10175466;
  double late_weight = 0.19657914;
  double critical_weight = 0.07608435;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
