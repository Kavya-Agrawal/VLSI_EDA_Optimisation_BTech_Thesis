// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49423221;
  double density_weight = 0.16164604;
  double prefix_weight = 0.42335584;
  double neighborhood_weight = 0.29791897;
  double late_weight = 0.02570076;
  double critical_weight = 0.02438105;
  unsigned budget = 33;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
