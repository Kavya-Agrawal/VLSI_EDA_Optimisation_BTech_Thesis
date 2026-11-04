// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35591120;
  double density_weight = 0.36794306;
  double prefix_weight = 0.28349129;
  double neighborhood_weight = 0.24241487;
  double late_weight = 0.28020358;
  double critical_weight = 0.23708442;
  unsigned budget = 17;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
