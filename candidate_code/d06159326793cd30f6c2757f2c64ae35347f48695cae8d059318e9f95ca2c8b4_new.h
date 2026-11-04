// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64842974;
  double density_weight = 0.37555078;
  double prefix_weight = 0.05648755;
  double neighborhood_weight = 0.07152377;
  double late_weight = 0.15819119;
  double critical_weight = 0.21222531;
  unsigned budget = 22;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
