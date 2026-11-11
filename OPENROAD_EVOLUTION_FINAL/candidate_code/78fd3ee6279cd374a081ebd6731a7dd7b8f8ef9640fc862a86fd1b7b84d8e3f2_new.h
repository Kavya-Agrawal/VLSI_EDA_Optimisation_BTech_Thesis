// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42965931;
  double density_weight = 0.23523026;
  double prefix_weight = 0.09612285;
  double neighborhood_weight = 0.36318327;
  double late_weight = 0.20719515;
  double critical_weight = 0.16206221;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
