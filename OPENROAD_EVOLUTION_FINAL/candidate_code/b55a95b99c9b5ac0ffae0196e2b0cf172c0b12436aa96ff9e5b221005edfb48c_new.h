// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13139272;
  double density_weight = 0.32222633;
  double prefix_weight = 0.17415341;
  double neighborhood_weight = 0.32234020;
  double late_weight = 0.05036626;
  double critical_weight = 0.34646235;
  unsigned budget = 16;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
