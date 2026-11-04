// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03235272;
  double density_weight = 0.55474050;
  double prefix_weight = 0.16790270;
  double neighborhood_weight = 0.02316092;
  double late_weight = 0.18562686;
  double critical_weight = 0.42345743;
  unsigned budget = 9;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
