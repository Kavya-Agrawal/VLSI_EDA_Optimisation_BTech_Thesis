// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78400807;
  double density_weight = 0.29578807;
  double prefix_weight = 0.26180456;
  double neighborhood_weight = 0.33219483;
  double late_weight = 0.23902396;
  double critical_weight = 0.05239275;
  unsigned budget = 27;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
