// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63415488;
  double density_weight = 0.08894946;
  double prefix_weight = 0.48162258;
  double neighborhood_weight = 0.25107566;
  double late_weight = 0.29961809;
  double critical_weight = 0.18433249;
  unsigned budget = 30;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
