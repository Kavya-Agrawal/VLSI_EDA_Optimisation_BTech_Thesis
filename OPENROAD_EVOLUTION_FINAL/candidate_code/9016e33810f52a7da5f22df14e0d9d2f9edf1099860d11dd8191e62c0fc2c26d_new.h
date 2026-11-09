// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62636470;
  double density_weight = 0.48556806;
  double prefix_weight = 0.43412232;
  double neighborhood_weight = 0.09870866;
  double late_weight = 0.00720967;
  double critical_weight = 0.35593779;
  unsigned budget = 20;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
