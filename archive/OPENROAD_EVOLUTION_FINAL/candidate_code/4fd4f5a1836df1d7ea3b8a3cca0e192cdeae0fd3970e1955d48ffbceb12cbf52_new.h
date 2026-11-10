// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22775723;
  double density_weight = 0.32779931;
  double prefix_weight = 0.31505811;
  double neighborhood_weight = 0.16984655;
  double late_weight = 0.12582463;
  double critical_weight = 0.26285833;
  unsigned budget = 32;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
