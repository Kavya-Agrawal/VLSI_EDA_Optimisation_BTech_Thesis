// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33062799;
  double density_weight = 0.45257538;
  double prefix_weight = 0.16457884;
  double neighborhood_weight = 0.13945144;
  double late_weight = 0.08112810;
  double critical_weight = 0.25367028;
  unsigned budget = 20;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
