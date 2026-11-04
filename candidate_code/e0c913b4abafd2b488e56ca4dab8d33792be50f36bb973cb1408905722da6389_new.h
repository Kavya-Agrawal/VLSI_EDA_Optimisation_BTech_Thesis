// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48598711;
  double density_weight = 0.46479961;
  double prefix_weight = 0.03969472;
  double neighborhood_weight = 0.22241967;
  double late_weight = 0.25565386;
  double critical_weight = 0.05255960;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
