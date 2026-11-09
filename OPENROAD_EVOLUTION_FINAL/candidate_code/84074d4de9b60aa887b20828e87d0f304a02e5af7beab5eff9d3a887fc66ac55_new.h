// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35852355;
  double density_weight = 0.36215392;
  double prefix_weight = 0.01810937;
  double neighborhood_weight = 0.15950839;
  double late_weight = 0.29849347;
  double critical_weight = 0.23163871;
  unsigned budget = 12;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
