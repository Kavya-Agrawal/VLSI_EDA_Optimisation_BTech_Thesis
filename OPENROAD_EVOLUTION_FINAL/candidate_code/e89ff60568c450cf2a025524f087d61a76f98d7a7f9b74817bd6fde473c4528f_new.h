// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53996493;
  double density_weight = 0.27566417;
  double prefix_weight = 0.20986733;
  double neighborhood_weight = 0.33035431;
  double late_weight = 0.03711509;
  double critical_weight = 0.17148949;
  unsigned budget = 12;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
