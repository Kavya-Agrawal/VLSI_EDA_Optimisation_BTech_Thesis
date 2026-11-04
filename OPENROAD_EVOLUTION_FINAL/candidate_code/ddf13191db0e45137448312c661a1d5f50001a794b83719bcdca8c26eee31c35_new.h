// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43192385;
  double density_weight = 0.25122384;
  double prefix_weight = 0.39453168;
  double neighborhood_weight = 0.06506394;
  double late_weight = 0.06583958;
  double critical_weight = 0.27685625;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
