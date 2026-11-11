// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59493165;
  double density_weight = 0.26197694;
  double prefix_weight = 0.44091581;
  double neighborhood_weight = 0.04141380;
  double late_weight = 0.08789342;
  double critical_weight = 0.45556431;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
