// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70944895;
  double density_weight = 0.52048751;
  double prefix_weight = 0.25441212;
  double neighborhood_weight = 0.01299563;
  double late_weight = 0.18645644;
  double critical_weight = 0.44547919;
  unsigned budget = 38;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
