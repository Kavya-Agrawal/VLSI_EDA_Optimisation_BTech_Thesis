// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44805833;
  double density_weight = 0.57518604;
  double prefix_weight = 0.07699919;
  double neighborhood_weight = 0.07910718;
  double late_weight = 0.01404474;
  double critical_weight = 0.49220767;
  unsigned budget = 36;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
