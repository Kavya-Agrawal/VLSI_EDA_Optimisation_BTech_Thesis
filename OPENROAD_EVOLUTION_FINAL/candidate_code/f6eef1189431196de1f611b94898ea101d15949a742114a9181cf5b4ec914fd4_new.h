// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00902861;
  double density_weight = 0.07318301;
  double prefix_weight = 0.48488629;
  double neighborhood_weight = 0.32520650;
  double late_weight = 0.18514162;
  double critical_weight = 0.21034775;
  unsigned budget = 24;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
