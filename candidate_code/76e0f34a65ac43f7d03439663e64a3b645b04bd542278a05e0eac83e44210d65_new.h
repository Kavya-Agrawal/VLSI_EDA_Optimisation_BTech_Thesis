// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35413695;
  double density_weight = 0.54979018;
  double prefix_weight = 0.41085998;
  double neighborhood_weight = 0.12581400;
  double late_weight = 0.22112869;
  double critical_weight = 0.44208389;
  unsigned budget = 24;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
