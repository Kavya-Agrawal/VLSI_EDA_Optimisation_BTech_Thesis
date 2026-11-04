// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78688691;
  double density_weight = 0.50911396;
  double prefix_weight = 0.24974691;
  double neighborhood_weight = 0.08848821;
  double late_weight = 0.29381555;
  double critical_weight = 0.05556917;
  unsigned budget = 32;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
