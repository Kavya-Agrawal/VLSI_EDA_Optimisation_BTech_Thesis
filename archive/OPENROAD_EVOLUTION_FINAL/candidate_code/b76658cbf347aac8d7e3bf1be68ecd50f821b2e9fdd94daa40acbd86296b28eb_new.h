// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44103647;
  double density_weight = 0.17927560;
  double prefix_weight = 0.34599455;
  double neighborhood_weight = 0.17069827;
  double late_weight = 0.25489849;
  double critical_weight = 0.16322432;
  unsigned budget = 40;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
