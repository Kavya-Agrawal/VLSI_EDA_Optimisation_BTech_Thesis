// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39768946;
  double density_weight = 0.23202192;
  double prefix_weight = 0.07251988;
  double neighborhood_weight = 0.28259626;
  double late_weight = 0.27347719;
  double critical_weight = 0.34793911;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
