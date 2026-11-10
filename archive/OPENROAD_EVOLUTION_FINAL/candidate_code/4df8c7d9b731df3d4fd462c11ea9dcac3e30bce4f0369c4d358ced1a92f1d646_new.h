// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37294715;
  double density_weight = 0.01423184;
  double prefix_weight = 0.10996217;
  double neighborhood_weight = 0.23730691;
  double late_weight = 0.07449143;
  double critical_weight = 0.12360856;
  unsigned budget = 40;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
