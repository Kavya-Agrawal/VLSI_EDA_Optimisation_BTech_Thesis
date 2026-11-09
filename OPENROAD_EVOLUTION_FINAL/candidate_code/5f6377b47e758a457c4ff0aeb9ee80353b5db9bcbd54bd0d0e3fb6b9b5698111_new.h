// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44347887;
  double density_weight = 0.31165180;
  double prefix_weight = 0.15618561;
  double neighborhood_weight = 0.23990079;
  double late_weight = 0.03436544;
  double critical_weight = 0.40424122;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
