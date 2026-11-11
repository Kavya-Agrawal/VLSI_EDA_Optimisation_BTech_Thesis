// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18025290;
  double density_weight = 0.07650031;
  double prefix_weight = 0.18436325;
  double neighborhood_weight = 0.16010524;
  double late_weight = 0.16979352;
  double critical_weight = 0.00704043;
  unsigned budget = 12;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
