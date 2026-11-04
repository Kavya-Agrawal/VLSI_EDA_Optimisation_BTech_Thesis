// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39530404;
  double density_weight = 0.52757000;
  double prefix_weight = 0.03427116;
  double neighborhood_weight = 0.39044287;
  double late_weight = 0.26622768;
  double critical_weight = 0.33725599;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
