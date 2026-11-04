// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29289660;
  double density_weight = 0.02336105;
  double prefix_weight = 0.38181519;
  double neighborhood_weight = 0.22762311;
  double late_weight = 0.28349704;
  double critical_weight = 0.48743286;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
