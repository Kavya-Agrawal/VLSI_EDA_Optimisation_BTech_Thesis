// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24755964;
  double density_weight = 0.11476867;
  double prefix_weight = 0.11128185;
  double neighborhood_weight = 0.24917815;
  double late_weight = 0.19836152;
  double critical_weight = 0.39122835;
  unsigned budget = 35;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
