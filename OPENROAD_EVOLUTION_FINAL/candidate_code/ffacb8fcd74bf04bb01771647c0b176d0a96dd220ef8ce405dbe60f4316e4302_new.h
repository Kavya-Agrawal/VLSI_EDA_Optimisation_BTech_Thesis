// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64557675;
  double density_weight = 0.15940997;
  double prefix_weight = 0.30526105;
  double neighborhood_weight = 0.18202783;
  double late_weight = 0.15700190;
  double critical_weight = 0.26228264;
  unsigned budget = 9;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
