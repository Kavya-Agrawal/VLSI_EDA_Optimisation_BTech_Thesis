// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62332491;
  double density_weight = 0.29286642;
  double prefix_weight = 0.03911733;
  double neighborhood_weight = 0.08491030;
  double late_weight = 0.21665150;
  double critical_weight = 0.24544214;
  unsigned budget = 35;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
