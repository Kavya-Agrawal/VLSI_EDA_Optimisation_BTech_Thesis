// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83313694;
  double density_weight = 0.18375562;
  double prefix_weight = 0.45844268;
  double neighborhood_weight = 0.07768244;
  double late_weight = 0.26390937;
  double critical_weight = 0.25309874;
  unsigned budget = 32;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
