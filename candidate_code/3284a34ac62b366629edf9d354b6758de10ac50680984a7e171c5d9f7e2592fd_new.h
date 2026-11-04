// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97701834;
  double density_weight = 0.04336785;
  double prefix_weight = 0.06798802;
  double neighborhood_weight = 0.11806628;
  double late_weight = 0.16522859;
  double critical_weight = 0.33944951;
  unsigned budget = 27;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
