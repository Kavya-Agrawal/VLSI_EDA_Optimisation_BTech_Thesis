// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01779062;
  double density_weight = 0.51412275;
  double prefix_weight = 0.10714605;
  double neighborhood_weight = 0.02839039;
  double late_weight = 0.01591801;
  double critical_weight = 0.34518218;
  unsigned budget = 37;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
