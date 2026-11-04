// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24975497;
  double density_weight = 0.42412428;
  double prefix_weight = 0.49297542;
  double neighborhood_weight = 0.31399553;
  double late_weight = 0.01835297;
  double critical_weight = 0.19210884;
  unsigned budget = 22;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
