// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09321604;
  double density_weight = 0.33292565;
  double prefix_weight = 0.47000171;
  double neighborhood_weight = 0.21439764;
  double late_weight = 0.12878813;
  double critical_weight = 0.29184577;
  unsigned budget = 17;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
