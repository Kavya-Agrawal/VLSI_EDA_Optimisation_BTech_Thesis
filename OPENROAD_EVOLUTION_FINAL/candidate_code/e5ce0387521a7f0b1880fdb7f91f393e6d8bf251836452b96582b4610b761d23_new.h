// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20465112;
  double density_weight = 0.16189283;
  double prefix_weight = 0.26708404;
  double neighborhood_weight = 0.11730455;
  double late_weight = 0.25112694;
  double critical_weight = 0.07759376;
  unsigned budget = 6;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
