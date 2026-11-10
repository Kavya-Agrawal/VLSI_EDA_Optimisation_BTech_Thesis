// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86002472;
  double density_weight = 0.11465173;
  double prefix_weight = 0.37792446;
  double neighborhood_weight = 0.21806612;
  double late_weight = 0.28909228;
  double critical_weight = 0.26886511;
  unsigned budget = 7;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
