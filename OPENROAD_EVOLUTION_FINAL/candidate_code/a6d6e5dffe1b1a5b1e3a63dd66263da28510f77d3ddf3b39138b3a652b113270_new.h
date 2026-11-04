// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55478631;
  double density_weight = 0.39532443;
  double prefix_weight = 0.35071906;
  double neighborhood_weight = 0.11266916;
  double late_weight = 0.24445535;
  double critical_weight = 0.33315697;
  unsigned budget = 21;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
