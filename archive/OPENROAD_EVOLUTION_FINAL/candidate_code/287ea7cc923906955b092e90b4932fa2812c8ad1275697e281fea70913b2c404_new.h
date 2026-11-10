// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87360482;
  double density_weight = 0.12363765;
  double prefix_weight = 0.32937525;
  double neighborhood_weight = 0.35835652;
  double late_weight = 0.05187872;
  double critical_weight = 0.12934519;
  unsigned budget = 35;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
