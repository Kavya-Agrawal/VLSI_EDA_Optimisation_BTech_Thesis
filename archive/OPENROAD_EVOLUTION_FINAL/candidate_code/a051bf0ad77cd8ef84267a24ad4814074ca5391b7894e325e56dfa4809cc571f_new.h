// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54813758;
  double density_weight = 0.07693872;
  double prefix_weight = 0.27552409;
  double neighborhood_weight = 0.25508416;
  double late_weight = 0.23095353;
  double critical_weight = 0.49862935;
  unsigned budget = 35;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
