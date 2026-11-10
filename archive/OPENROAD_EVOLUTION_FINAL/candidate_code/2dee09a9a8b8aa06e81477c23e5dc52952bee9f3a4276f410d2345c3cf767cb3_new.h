// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74760713;
  double density_weight = 0.02608815;
  double prefix_weight = 0.36629938;
  double neighborhood_weight = 0.05036996;
  double late_weight = 0.19456090;
  double critical_weight = 0.03106135;
  unsigned budget = 15;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
