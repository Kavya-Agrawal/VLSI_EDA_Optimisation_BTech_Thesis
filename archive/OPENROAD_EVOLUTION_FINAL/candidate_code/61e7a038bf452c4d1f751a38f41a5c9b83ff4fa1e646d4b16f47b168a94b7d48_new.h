// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01982271;
  double density_weight = 0.35635917;
  double prefix_weight = 0.23949034;
  double neighborhood_weight = 0.28517214;
  double late_weight = 0.01979453;
  double critical_weight = 0.36100456;
  unsigned budget = 31;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
