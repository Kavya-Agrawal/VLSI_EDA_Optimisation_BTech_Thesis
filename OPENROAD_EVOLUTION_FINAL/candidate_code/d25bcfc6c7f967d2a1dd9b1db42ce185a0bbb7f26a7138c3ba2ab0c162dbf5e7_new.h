// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56248317;
  double density_weight = 0.44570065;
  double prefix_weight = 0.09061383;
  double neighborhood_weight = 0.18672154;
  double late_weight = 0.27646872;
  double critical_weight = 0.27394058;
  unsigned budget = 9;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
