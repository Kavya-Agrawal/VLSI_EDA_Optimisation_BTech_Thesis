// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31244521;
  double density_weight = 0.14190535;
  double prefix_weight = 0.48038437;
  double neighborhood_weight = 0.01680110;
  double late_weight = 0.05603400;
  double critical_weight = 0.34742195;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
