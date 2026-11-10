// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07920492;
  double density_weight = 0.41075281;
  double prefix_weight = 0.21586843;
  double neighborhood_weight = 0.07533069;
  double late_weight = 0.16281544;
  double critical_weight = 0.44487022;
  unsigned budget = 26;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
