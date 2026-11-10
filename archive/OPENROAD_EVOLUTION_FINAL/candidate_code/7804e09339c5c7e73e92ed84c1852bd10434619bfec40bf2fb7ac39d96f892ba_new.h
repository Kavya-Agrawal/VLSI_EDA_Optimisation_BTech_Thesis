// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98794125;
  double density_weight = 0.12450737;
  double prefix_weight = 0.41195854;
  double neighborhood_weight = 0.02334214;
  double late_weight = 0.18450480;
  double critical_weight = 0.03532941;
  unsigned budget = 22;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
