// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17895354;
  double density_weight = 0.52016105;
  double prefix_weight = 0.47282057;
  double neighborhood_weight = 0.25711858;
  double late_weight = 0.12480099;
  double critical_weight = 0.14326026;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
