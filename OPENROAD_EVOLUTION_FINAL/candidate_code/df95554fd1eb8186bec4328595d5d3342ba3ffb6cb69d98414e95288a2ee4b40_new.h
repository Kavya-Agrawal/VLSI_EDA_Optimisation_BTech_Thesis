// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40496046;
  double density_weight = 0.51477394;
  double prefix_weight = 0.20907138;
  double neighborhood_weight = 0.28129985;
  double late_weight = 0.16426775;
  double critical_weight = 0.47285147;
  unsigned budget = 26;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
