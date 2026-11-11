// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21579959;
  double density_weight = 0.00329658;
  double prefix_weight = 0.23443338;
  double neighborhood_weight = 0.18535514;
  double late_weight = 0.22750657;
  double critical_weight = 0.37606783;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
