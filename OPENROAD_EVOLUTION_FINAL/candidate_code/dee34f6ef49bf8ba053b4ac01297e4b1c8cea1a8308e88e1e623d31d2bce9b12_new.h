// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40130089;
  double density_weight = 0.24583465;
  double prefix_weight = 0.46151497;
  double neighborhood_weight = 0.06730279;
  double late_weight = 0.25529172;
  double critical_weight = 0.32544861;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
