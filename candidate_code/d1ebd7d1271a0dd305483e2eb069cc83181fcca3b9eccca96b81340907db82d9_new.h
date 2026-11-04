// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54253605;
  double density_weight = 0.45746437;
  double prefix_weight = 0.01350529;
  double neighborhood_weight = 0.14940214;
  double late_weight = 0.18249393;
  double critical_weight = 0.32681694;
  unsigned budget = 16;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
