// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83668351;
  double density_weight = 0.42131898;
  double prefix_weight = 0.24060432;
  double neighborhood_weight = 0.36530522;
  double late_weight = 0.15673280;
  double critical_weight = 0.32969451;
  unsigned budget = 25;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
