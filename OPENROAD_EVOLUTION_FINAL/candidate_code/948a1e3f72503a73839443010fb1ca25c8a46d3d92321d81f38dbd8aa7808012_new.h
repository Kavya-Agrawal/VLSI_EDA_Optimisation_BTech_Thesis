// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94257677;
  double density_weight = 0.10970397;
  double prefix_weight = 0.31001431;
  double neighborhood_weight = 0.09296621;
  double late_weight = 0.08124061;
  double critical_weight = 0.16007199;
  unsigned budget = 16;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
