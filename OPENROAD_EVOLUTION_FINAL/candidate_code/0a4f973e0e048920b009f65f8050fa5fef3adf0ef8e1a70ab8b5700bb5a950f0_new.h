// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81273535;
  double density_weight = 0.27509824;
  double prefix_weight = 0.12019014;
  double neighborhood_weight = 0.34609982;
  double late_weight = 0.12228973;
  double critical_weight = 0.29849007;
  unsigned budget = 34;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
