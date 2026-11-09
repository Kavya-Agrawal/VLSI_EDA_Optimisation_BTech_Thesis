// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20693687;
  double density_weight = 0.32669328;
  double prefix_weight = 0.14446230;
  double neighborhood_weight = 0.30011784;
  double late_weight = 0.07310975;
  double critical_weight = 0.09421892;
  unsigned budget = 19;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
