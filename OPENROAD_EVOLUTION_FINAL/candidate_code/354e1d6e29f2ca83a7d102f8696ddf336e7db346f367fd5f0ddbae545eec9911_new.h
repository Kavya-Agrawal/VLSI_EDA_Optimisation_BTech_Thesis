// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27177851;
  double density_weight = 0.24635895;
  double prefix_weight = 0.43533054;
  double neighborhood_weight = 0.20013876;
  double late_weight = 0.04477680;
  double critical_weight = 0.46898970;
  unsigned budget = 29;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
