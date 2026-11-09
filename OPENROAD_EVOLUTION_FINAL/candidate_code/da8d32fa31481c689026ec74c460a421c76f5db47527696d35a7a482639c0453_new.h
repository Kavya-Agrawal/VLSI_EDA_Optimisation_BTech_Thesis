// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00317760;
  double density_weight = 0.19017801;
  double prefix_weight = 0.13482715;
  double neighborhood_weight = 0.11652099;
  double late_weight = 0.25905020;
  double critical_weight = 0.01496069;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
