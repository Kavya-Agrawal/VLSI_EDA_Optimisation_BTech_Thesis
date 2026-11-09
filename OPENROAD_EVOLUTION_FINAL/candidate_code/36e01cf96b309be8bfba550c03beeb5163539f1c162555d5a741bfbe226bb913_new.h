// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16744484;
  double density_weight = 0.24164181;
  double prefix_weight = 0.35814893;
  double neighborhood_weight = 0.13276804;
  double late_weight = 0.06038950;
  double critical_weight = 0.45990042;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
