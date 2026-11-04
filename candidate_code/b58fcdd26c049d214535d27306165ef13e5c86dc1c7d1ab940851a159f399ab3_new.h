// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44294201;
  double density_weight = 0.55616092;
  double prefix_weight = 0.35627553;
  double neighborhood_weight = 0.16838890;
  double late_weight = 0.11469894;
  double critical_weight = 0.28726839;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
