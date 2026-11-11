// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64161350;
  double density_weight = 0.11332505;
  double prefix_weight = 0.21838998;
  double neighborhood_weight = 0.33660391;
  double late_weight = 0.14541154;
  double critical_weight = 0.33831583;
  unsigned budget = 39;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
