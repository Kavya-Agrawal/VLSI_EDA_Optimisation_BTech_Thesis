// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13450736;
  double density_weight = 0.34812955;
  double prefix_weight = 0.42710885;
  double neighborhood_weight = 0.31687538;
  double late_weight = 0.01203183;
  double critical_weight = 0.24785699;
  unsigned budget = 16;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
