// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18063858;
  double density_weight = 0.04792855;
  double prefix_weight = 0.14971909;
  double neighborhood_weight = 0.07030711;
  double late_weight = 0.04470440;
  double critical_weight = 0.48523440;
  unsigned budget = 37;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
