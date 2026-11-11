// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62548863;
  double density_weight = 0.26925182;
  double prefix_weight = 0.28657303;
  double neighborhood_weight = 0.20529580;
  double late_weight = 0.11377793;
  double critical_weight = 0.44114919;
  unsigned budget = 39;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
