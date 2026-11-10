// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28784174;
  double density_weight = 0.30853157;
  double prefix_weight = 0.20168839;
  double neighborhood_weight = 0.16636806;
  double late_weight = 0.04169329;
  double critical_weight = 0.42477727;
  unsigned budget = 10;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
