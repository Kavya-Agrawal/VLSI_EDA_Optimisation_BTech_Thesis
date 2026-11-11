// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39984213;
  double density_weight = 0.58092959;
  double prefix_weight = 0.06903388;
  double neighborhood_weight = 0.39059373;
  double late_weight = 0.09404436;
  double critical_weight = 0.49488386;
  unsigned budget = 14;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
