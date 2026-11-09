// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83090050;
  double density_weight = 0.43821052;
  double prefix_weight = 0.03966339;
  double neighborhood_weight = 0.11161569;
  double late_weight = 0.18568955;
  double critical_weight = 0.40530440;
  unsigned budget = 14;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
