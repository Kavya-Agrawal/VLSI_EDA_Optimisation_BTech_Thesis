// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19146839;
  double density_weight = 0.13049005;
  double prefix_weight = 0.18139141;
  double neighborhood_weight = 0.37987975;
  double late_weight = 0.18734287;
  double critical_weight = 0.31344104;
  unsigned budget = 27;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
