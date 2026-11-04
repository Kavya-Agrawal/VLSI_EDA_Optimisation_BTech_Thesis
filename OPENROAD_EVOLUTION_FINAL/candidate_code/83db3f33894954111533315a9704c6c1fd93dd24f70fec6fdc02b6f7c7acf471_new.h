// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61019981;
  double density_weight = 0.00419886;
  double prefix_weight = 0.36208923;
  double neighborhood_weight = 0.22862596;
  double late_weight = 0.20812166;
  double critical_weight = 0.28907194;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
