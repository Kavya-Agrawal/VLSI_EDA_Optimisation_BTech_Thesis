// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02018488;
  double density_weight = 0.16607925;
  double prefix_weight = 0.05953653;
  double neighborhood_weight = 0.38369920;
  double late_weight = 0.05766390;
  double critical_weight = 0.14038262;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
