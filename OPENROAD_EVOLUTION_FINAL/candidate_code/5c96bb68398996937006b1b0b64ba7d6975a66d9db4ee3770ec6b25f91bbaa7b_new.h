// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25344007;
  double density_weight = 0.52960753;
  double prefix_weight = 0.29180342;
  double neighborhood_weight = 0.33563843;
  double late_weight = 0.15775725;
  double critical_weight = 0.29547863;
  unsigned budget = 31;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
