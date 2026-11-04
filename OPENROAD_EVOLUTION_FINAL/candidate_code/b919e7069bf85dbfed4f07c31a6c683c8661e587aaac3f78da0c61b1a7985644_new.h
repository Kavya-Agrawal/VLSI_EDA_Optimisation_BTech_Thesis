// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84396764;
  double density_weight = 0.41249468;
  double prefix_weight = 0.06369222;
  double neighborhood_weight = 0.26239302;
  double late_weight = 0.26494412;
  double critical_weight = 0.22452821;
  unsigned budget = 30;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
