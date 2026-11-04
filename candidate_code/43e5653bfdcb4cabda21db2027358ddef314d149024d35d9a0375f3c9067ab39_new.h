// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57700077;
  double density_weight = 0.38686796;
  double prefix_weight = 0.35882531;
  double neighborhood_weight = 0.07186558;
  double late_weight = 0.22181701;
  double critical_weight = 0.37622457;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
