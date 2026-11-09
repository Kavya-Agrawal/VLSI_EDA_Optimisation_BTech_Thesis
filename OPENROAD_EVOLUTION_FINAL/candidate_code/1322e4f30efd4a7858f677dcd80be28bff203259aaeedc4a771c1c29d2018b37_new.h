// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45127634;
  double density_weight = 0.04125666;
  double prefix_weight = 0.05322162;
  double neighborhood_weight = 0.07199917;
  double late_weight = 0.02519669;
  double critical_weight = 0.49212026;
  unsigned budget = 4;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
