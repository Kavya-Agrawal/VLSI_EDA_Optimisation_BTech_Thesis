// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57215704;
  double density_weight = 0.45202024;
  double prefix_weight = 0.30440621;
  double neighborhood_weight = 0.03784245;
  double late_weight = 0.17625760;
  double critical_weight = 0.19258358;
  unsigned budget = 5;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
