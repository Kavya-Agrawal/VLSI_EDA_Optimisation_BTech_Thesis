// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31471039;
  double density_weight = 0.36560062;
  double prefix_weight = 0.13963474;
  double neighborhood_weight = 0.05642607;
  double late_weight = 0.11646881;
  double critical_weight = 0.03061070;
  unsigned budget = 36;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
