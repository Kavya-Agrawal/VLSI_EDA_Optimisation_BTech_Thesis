// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89269712;
  double density_weight = 0.14709907;
  double prefix_weight = 0.27192880;
  double neighborhood_weight = 0.30323376;
  double late_weight = 0.17754287;
  double critical_weight = 0.39279128;
  unsigned budget = 22;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
