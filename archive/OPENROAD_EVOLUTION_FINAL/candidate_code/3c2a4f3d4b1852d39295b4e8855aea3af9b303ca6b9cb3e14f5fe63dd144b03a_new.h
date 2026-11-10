// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76266585;
  double density_weight = 0.40678478;
  double prefix_weight = 0.06651320;
  double neighborhood_weight = 0.28630931;
  double late_weight = 0.01266860;
  double critical_weight = 0.03978505;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
