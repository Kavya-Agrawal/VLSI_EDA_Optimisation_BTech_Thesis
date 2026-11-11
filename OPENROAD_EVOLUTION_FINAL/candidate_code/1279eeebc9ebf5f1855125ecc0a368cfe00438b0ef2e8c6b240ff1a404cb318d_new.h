// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61877041;
  double density_weight = 0.16179039;
  double prefix_weight = 0.03298710;
  double neighborhood_weight = 0.04993328;
  double late_weight = 0.15484978;
  double critical_weight = 0.30031222;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
