// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31761997;
  double density_weight = 0.18043979;
  double prefix_weight = 0.33494141;
  double neighborhood_weight = 0.32797584;
  double late_weight = 0.19368050;
  double critical_weight = 0.14303377;
  unsigned budget = 18;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
