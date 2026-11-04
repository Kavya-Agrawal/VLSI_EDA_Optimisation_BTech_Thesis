// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90265103;
  double density_weight = 0.24598592;
  double prefix_weight = 0.41397792;
  double neighborhood_weight = 0.09102742;
  double late_weight = 0.25058854;
  double critical_weight = 0.41779611;
  unsigned budget = 33;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
