// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90402795;
  double density_weight = 0.01464993;
  double prefix_weight = 0.40185795;
  double neighborhood_weight = 0.37570114;
  double late_weight = 0.21070358;
  double critical_weight = 0.43502101;
  unsigned budget = 7;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
