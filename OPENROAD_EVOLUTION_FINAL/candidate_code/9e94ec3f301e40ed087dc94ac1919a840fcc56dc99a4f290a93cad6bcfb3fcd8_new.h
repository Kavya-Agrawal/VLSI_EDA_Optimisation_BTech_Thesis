// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19719220;
  double density_weight = 0.25220806;
  double prefix_weight = 0.45118272;
  double neighborhood_weight = 0.28279250;
  double late_weight = 0.15015867;
  double critical_weight = 0.29395618;
  unsigned budget = 13;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
