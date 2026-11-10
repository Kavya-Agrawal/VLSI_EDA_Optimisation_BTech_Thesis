// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39779664;
  double density_weight = 0.09070172;
  double prefix_weight = 0.03949293;
  double neighborhood_weight = 0.06747081;
  double late_weight = 0.00467466;
  double critical_weight = 0.38727120;
  unsigned budget = 4;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
