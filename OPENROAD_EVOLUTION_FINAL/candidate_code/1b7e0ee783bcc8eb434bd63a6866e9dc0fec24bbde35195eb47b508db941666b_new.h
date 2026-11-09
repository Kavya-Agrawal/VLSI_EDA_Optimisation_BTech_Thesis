// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59455231;
  double density_weight = 0.39144676;
  double prefix_weight = 0.08773133;
  double neighborhood_weight = 0.30670919;
  double late_weight = 0.24204769;
  double critical_weight = 0.04816882;
  unsigned budget = 28;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
