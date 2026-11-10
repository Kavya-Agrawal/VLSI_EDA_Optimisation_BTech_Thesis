// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40938537;
  double density_weight = 0.45859158;
  double prefix_weight = 0.49024356;
  double neighborhood_weight = 0.16529167;
  double late_weight = 0.18735444;
  double critical_weight = 0.22430125;
  unsigned budget = 19;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
