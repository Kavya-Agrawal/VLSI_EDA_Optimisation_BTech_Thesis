// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23782351;
  double density_weight = 0.29873797;
  double prefix_weight = 0.49193062;
  double neighborhood_weight = 0.26547783;
  double late_weight = 0.14287281;
  double critical_weight = 0.27611427;
  unsigned budget = 10;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
