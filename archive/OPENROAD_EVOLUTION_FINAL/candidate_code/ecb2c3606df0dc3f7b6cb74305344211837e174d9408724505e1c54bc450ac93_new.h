// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22373764;
  double density_weight = 0.49451862;
  double prefix_weight = 0.18324576;
  double neighborhood_weight = 0.31565029;
  double late_weight = 0.27410889;
  double critical_weight = 0.41957472;
  unsigned budget = 16;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
