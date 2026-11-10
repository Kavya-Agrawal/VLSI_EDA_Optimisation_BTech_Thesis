// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05321537;
  double density_weight = 0.48122625;
  double prefix_weight = 0.22508866;
  double neighborhood_weight = 0.17478299;
  double late_weight = 0.03829321;
  double critical_weight = 0.13926217;
  unsigned budget = 40;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
