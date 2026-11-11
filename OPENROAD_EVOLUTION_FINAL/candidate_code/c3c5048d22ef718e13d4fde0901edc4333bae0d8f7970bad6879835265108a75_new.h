// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52883598;
  double density_weight = 0.53394546;
  double prefix_weight = 0.04513599;
  double neighborhood_weight = 0.09502503;
  double late_weight = 0.03599116;
  double critical_weight = 0.38518486;
  unsigned budget = 22;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
