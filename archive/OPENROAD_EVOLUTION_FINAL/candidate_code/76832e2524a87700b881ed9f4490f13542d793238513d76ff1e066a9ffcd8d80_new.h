// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47848323;
  double density_weight = 0.15658558;
  double prefix_weight = 0.38779698;
  double neighborhood_weight = 0.16506195;
  double late_weight = 0.11426580;
  double critical_weight = 0.38715151;
  unsigned budget = 27;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
