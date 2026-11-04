// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45287706;
  double density_weight = 0.58661676;
  double prefix_weight = 0.24958247;
  double neighborhood_weight = 0.37416567;
  double late_weight = 0.21495738;
  double critical_weight = 0.27649937;
  unsigned budget = 13;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
