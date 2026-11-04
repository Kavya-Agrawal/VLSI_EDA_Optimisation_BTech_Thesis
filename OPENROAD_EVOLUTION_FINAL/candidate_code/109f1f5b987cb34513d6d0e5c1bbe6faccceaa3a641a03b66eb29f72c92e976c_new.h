// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07801458;
  double density_weight = 0.14486101;
  double prefix_weight = 0.06419885;
  double neighborhood_weight = 0.29937905;
  double late_weight = 0.03120124;
  double critical_weight = 0.30785226;
  unsigned budget = 36;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
