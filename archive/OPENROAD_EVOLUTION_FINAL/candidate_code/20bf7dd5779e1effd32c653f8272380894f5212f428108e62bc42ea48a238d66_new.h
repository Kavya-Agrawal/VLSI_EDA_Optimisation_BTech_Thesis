// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14511458;
  double density_weight = 0.46221261;
  double prefix_weight = 0.40317594;
  double neighborhood_weight = 0.30723852;
  double late_weight = 0.26670912;
  double critical_weight = 0.44079593;
  unsigned budget = 29;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
