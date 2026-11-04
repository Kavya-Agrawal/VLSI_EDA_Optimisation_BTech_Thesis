// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19757025;
  double density_weight = 0.25295941;
  double prefix_weight = 0.38940021;
  double neighborhood_weight = 0.11894571;
  double late_weight = 0.09272724;
  double critical_weight = 0.26971228;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
