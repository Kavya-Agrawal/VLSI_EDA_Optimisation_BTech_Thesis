// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11152815;
  double density_weight = 0.29184776;
  double prefix_weight = 0.15474321;
  double neighborhood_weight = 0.23472658;
  double late_weight = 0.29035972;
  double critical_weight = 0.05615905;
  unsigned budget = 32;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
