// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80713889;
  double density_weight = 0.59356956;
  double prefix_weight = 0.19161578;
  double neighborhood_weight = 0.12605363;
  double late_weight = 0.09658519;
  double critical_weight = 0.41475064;
  unsigned budget = 5;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
