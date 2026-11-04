// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10186051;
  double density_weight = 0.58629413;
  double prefix_weight = 0.20770489;
  double neighborhood_weight = 0.07310837;
  double late_weight = 0.26150713;
  double critical_weight = 0.24820568;
  unsigned budget = 35;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
