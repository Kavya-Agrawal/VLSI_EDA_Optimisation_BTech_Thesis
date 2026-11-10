// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55514018;
  double density_weight = 0.36196048;
  double prefix_weight = 0.03154706;
  double neighborhood_weight = 0.26211497;
  double late_weight = 0.19811378;
  double critical_weight = 0.20057060;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
