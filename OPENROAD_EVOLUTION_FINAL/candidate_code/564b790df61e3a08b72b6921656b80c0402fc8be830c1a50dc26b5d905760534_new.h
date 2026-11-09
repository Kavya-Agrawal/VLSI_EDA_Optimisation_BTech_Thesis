// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43301277;
  double density_weight = 0.20035085;
  double prefix_weight = 0.08884813;
  double neighborhood_weight = 0.24501789;
  double late_weight = 0.16972073;
  double critical_weight = 0.08617970;
  unsigned budget = 10;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
