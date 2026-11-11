// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10031808;
  double density_weight = 0.50901526;
  double prefix_weight = 0.32010778;
  double neighborhood_weight = 0.19239867;
  double late_weight = 0.23131791;
  double critical_weight = 0.17688441;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
