// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86876822;
  double density_weight = 0.33495723;
  double prefix_weight = 0.30415167;
  double neighborhood_weight = 0.10069346;
  double late_weight = 0.02040163;
  double critical_weight = 0.27790490;
  unsigned budget = 39;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
