// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82757883;
  double density_weight = 0.25301198;
  double prefix_weight = 0.34639052;
  double neighborhood_weight = 0.19555742;
  double late_weight = 0.14657671;
  double critical_weight = 0.24562706;
  unsigned budget = 23;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
