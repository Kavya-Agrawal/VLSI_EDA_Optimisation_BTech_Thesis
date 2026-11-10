// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07684593;
  double density_weight = 0.59260099;
  double prefix_weight = 0.19751952;
  double neighborhood_weight = 0.10193709;
  double late_weight = 0.13415050;
  double critical_weight = 0.31245372;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
