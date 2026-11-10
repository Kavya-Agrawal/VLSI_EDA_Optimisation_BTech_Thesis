// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94137790;
  double density_weight = 0.54562739;
  double prefix_weight = 0.00706876;
  double neighborhood_weight = 0.06208706;
  double late_weight = 0.24963909;
  double critical_weight = 0.26309071;
  unsigned budget = 34;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
