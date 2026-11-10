// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74828997;
  double density_weight = 0.53042636;
  double prefix_weight = 0.18622869;
  double neighborhood_weight = 0.06221783;
  double late_weight = 0.08042753;
  double critical_weight = 0.49868133;
  unsigned budget = 29;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
