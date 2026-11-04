// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29886036;
  double density_weight = 0.25302377;
  double prefix_weight = 0.17890613;
  double neighborhood_weight = 0.16860083;
  double late_weight = 0.15096412;
  double critical_weight = 0.39135085;
  unsigned budget = 40;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
