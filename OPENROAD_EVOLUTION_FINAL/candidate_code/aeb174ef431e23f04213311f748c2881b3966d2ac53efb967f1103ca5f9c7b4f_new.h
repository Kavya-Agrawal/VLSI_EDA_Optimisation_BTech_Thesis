// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41506355;
  double density_weight = 0.47581470;
  double prefix_weight = 0.14430128;
  double neighborhood_weight = 0.09359699;
  double late_weight = 0.27666049;
  double critical_weight = 0.41336398;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
