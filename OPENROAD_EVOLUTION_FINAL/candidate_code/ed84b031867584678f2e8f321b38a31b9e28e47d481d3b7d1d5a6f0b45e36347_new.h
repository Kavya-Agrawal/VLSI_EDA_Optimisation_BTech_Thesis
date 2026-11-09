// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36394766;
  double density_weight = 0.57496810;
  double prefix_weight = 0.35929051;
  double neighborhood_weight = 0.03248506;
  double late_weight = 0.08296953;
  double critical_weight = 0.39185359;
  unsigned budget = 4;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
