// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23963773;
  double density_weight = 0.03155745;
  double prefix_weight = 0.08649825;
  double neighborhood_weight = 0.39067495;
  double late_weight = 0.07677786;
  double critical_weight = 0.26522116;
  unsigned budget = 13;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
