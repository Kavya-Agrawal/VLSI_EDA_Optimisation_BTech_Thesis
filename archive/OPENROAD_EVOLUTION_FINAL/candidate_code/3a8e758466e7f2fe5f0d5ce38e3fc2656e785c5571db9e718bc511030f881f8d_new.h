// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10116945;
  double density_weight = 0.23359800;
  double prefix_weight = 0.21070038;
  double neighborhood_weight = 0.18462711;
  double late_weight = 0.04238065;
  double critical_weight = 0.45263274;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
