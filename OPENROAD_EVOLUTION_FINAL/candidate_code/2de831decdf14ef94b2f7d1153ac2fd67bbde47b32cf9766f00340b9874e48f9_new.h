// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64039529;
  double density_weight = 0.57233375;
  double prefix_weight = 0.40665482;
  double neighborhood_weight = 0.13773602;
  double late_weight = 0.28622750;
  double critical_weight = 0.37006882;
  unsigned budget = 21;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
