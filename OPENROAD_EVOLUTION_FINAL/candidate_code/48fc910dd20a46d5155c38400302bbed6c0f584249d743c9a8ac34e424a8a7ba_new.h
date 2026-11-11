// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88115704;
  double density_weight = 0.41964852;
  double prefix_weight = 0.42001352;
  double neighborhood_weight = 0.14547583;
  double late_weight = 0.09473968;
  double critical_weight = 0.27639732;
  unsigned budget = 4;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
