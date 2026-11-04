// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87998288;
  double density_weight = 0.29850177;
  double prefix_weight = 0.28386618;
  double neighborhood_weight = 0.25697088;
  double late_weight = 0.14728853;
  double critical_weight = 0.24541624;
  unsigned budget = 40;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
