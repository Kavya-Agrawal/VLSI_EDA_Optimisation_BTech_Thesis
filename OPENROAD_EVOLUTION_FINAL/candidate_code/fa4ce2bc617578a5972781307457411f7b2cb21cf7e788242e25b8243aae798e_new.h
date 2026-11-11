// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85136898;
  double density_weight = 0.12131718;
  double prefix_weight = 0.40889116;
  double neighborhood_weight = 0.06519033;
  double late_weight = 0.22309940;
  double critical_weight = 0.44935997;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
