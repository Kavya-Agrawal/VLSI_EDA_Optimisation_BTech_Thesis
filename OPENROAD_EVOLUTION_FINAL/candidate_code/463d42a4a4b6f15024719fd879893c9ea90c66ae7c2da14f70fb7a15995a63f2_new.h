// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57949005;
  double density_weight = 0.54528216;
  double prefix_weight = 0.30862407;
  double neighborhood_weight = 0.32189486;
  double late_weight = 0.17339794;
  double critical_weight = 0.02862547;
  unsigned budget = 15;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
