// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57104275;
  double density_weight = 0.57990972;
  double prefix_weight = 0.39030442;
  double neighborhood_weight = 0.11162099;
  double late_weight = 0.28932602;
  double critical_weight = 0.49951467;
  unsigned budget = 9;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
