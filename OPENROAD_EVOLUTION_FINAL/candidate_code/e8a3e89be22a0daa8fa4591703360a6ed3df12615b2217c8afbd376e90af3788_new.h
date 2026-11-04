// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62180480;
  double density_weight = 0.09706167;
  double prefix_weight = 0.38233635;
  double neighborhood_weight = 0.01118036;
  double late_weight = 0.01713726;
  double critical_weight = 0.40111341;
  unsigned budget = 6;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
