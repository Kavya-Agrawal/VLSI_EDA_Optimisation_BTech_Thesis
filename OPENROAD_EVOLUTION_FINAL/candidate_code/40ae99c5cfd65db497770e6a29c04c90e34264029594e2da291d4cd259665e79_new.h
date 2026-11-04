// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93626241;
  double density_weight = 0.43107774;
  double prefix_weight = 0.00696119;
  double neighborhood_weight = 0.30374093;
  double late_weight = 0.18376581;
  double critical_weight = 0.32626231;
  unsigned budget = 40;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
