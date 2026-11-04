// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19053988;
  double density_weight = 0.25703122;
  double prefix_weight = 0.46062470;
  double neighborhood_weight = 0.25895957;
  double late_weight = 0.04221310;
  double critical_weight = 0.16536529;
  unsigned budget = 29;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
