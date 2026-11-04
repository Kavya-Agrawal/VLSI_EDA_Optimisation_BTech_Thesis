// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86399371;
  double density_weight = 0.39169225;
  double prefix_weight = 0.33193213;
  double neighborhood_weight = 0.11374613;
  double late_weight = 0.05907622;
  double critical_weight = 0.36777080;
  unsigned budget = 7;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
