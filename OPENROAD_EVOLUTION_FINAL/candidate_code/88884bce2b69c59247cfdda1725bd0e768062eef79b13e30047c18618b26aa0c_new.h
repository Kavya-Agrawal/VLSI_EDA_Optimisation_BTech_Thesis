// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62883228;
  double density_weight = 0.00102868;
  double prefix_weight = 0.17691736;
  double neighborhood_weight = 0.35196504;
  double late_weight = 0.13479950;
  double critical_weight = 0.02894929;
  unsigned budget = 24;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
