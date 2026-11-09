// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27444940;
  double density_weight = 0.24241868;
  double prefix_weight = 0.20335772;
  double neighborhood_weight = 0.30914012;
  double late_weight = 0.12918804;
  double critical_weight = 0.42642351;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
