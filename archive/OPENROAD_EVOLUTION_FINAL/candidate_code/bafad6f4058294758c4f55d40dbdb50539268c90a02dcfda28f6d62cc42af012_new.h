// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72986033;
  double density_weight = 0.46576255;
  double prefix_weight = 0.49628481;
  double neighborhood_weight = 0.08800353;
  double late_weight = 0.05820974;
  double critical_weight = 0.48321732;
  unsigned budget = 18;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
