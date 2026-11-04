// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35624799;
  double density_weight = 0.57441307;
  double prefix_weight = 0.39459530;
  double neighborhood_weight = 0.27323474;
  double late_weight = 0.27190962;
  double critical_weight = 0.33130764;
  unsigned budget = 33;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
