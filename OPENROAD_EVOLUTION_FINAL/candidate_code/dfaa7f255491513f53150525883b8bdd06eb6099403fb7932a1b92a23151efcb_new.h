// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48376011;
  double density_weight = 0.50762978;
  double prefix_weight = 0.46816293;
  double neighborhood_weight = 0.20989755;
  double late_weight = 0.22157997;
  double critical_weight = 0.03041661;
  unsigned budget = 10;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
