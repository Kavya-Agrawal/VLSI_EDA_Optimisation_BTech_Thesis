// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66944492;
  double density_weight = 0.41734739;
  double prefix_weight = 0.37237310;
  double neighborhood_weight = 0.11625254;
  double late_weight = 0.28920047;
  double critical_weight = 0.19664229;
  unsigned budget = 30;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
