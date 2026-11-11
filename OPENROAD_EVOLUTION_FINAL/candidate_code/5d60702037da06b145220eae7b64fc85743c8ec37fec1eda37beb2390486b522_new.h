// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48076334;
  double density_weight = 0.26927971;
  double prefix_weight = 0.10104816;
  double neighborhood_weight = 0.38411716;
  double late_weight = 0.08158733;
  double critical_weight = 0.45979546;
  unsigned budget = 31;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
