// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76623436;
  double density_weight = 0.49123962;
  double prefix_weight = 0.37397361;
  double neighborhood_weight = 0.13250902;
  double late_weight = 0.01441555;
  double critical_weight = 0.02360101;
  unsigned budget = 8;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
