// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06953758;
  double density_weight = 0.33276948;
  double prefix_weight = 0.26024681;
  double neighborhood_weight = 0.05763610;
  double late_weight = 0.28752027;
  double critical_weight = 0.48139024;
  unsigned budget = 11;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
