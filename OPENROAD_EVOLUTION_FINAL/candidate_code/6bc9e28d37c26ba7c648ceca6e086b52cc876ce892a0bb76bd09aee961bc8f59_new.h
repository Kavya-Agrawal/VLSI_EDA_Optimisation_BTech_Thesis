// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61077790;
  double density_weight = 0.22862045;
  double prefix_weight = 0.47601458;
  double neighborhood_weight = 0.29584943;
  double late_weight = 0.27948709;
  double critical_weight = 0.44811458;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
