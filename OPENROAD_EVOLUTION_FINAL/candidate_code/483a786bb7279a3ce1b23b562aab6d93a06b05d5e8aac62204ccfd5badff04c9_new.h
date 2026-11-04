// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56942522;
  double density_weight = 0.47895425;
  double prefix_weight = 0.38740497;
  double neighborhood_weight = 0.33298673;
  double late_weight = 0.20864369;
  double critical_weight = 0.32427879;
  unsigned budget = 12;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
