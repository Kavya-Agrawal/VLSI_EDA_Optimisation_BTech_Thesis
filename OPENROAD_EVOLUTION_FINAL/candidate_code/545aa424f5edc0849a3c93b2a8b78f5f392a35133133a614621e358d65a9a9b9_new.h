// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10854582;
  double density_weight = 0.23361315;
  double prefix_weight = 0.09148826;
  double neighborhood_weight = 0.17680217;
  double late_weight = 0.24455491;
  double critical_weight = 0.29455690;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
