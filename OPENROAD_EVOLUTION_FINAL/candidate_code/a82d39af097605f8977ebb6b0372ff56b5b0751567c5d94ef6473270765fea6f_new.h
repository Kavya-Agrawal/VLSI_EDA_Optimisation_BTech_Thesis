// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93004087;
  double density_weight = 0.04133608;
  double prefix_weight = 0.24813331;
  double neighborhood_weight = 0.25725904;
  double late_weight = 0.12831274;
  double critical_weight = 0.31733163;
  unsigned budget = 25;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
