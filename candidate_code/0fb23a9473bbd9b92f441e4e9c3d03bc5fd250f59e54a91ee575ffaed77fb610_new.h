// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95813459;
  double density_weight = 0.06668165;
  double prefix_weight = 0.43697375;
  double neighborhood_weight = 0.28920521;
  double late_weight = 0.25312107;
  double critical_weight = 0.43409501;
  unsigned budget = 30;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
