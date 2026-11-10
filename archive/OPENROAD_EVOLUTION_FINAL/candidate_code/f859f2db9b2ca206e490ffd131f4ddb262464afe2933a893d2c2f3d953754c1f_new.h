// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84336497;
  double density_weight = 0.42470434;
  double prefix_weight = 0.46175113;
  double neighborhood_weight = 0.37150602;
  double late_weight = 0.24323070;
  double critical_weight = 0.28702645;
  unsigned budget = 19;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
