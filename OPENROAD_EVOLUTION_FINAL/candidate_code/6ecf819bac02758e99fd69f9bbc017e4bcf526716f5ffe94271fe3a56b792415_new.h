// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17544954;
  double density_weight = 0.50184920;
  double prefix_weight = 0.02428986;
  double neighborhood_weight = 0.22080301;
  double late_weight = 0.12439427;
  double critical_weight = 0.47276669;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
