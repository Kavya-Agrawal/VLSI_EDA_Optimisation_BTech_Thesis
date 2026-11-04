// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92402917;
  double density_weight = 0.26046918;
  double prefix_weight = 0.48696967;
  double neighborhood_weight = 0.28334587;
  double late_weight = 0.11388215;
  double critical_weight = 0.03504828;
  unsigned budget = 31;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
