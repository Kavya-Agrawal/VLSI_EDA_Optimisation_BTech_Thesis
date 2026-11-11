// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46130286;
  double density_weight = 0.13182458;
  double prefix_weight = 0.16125722;
  double neighborhood_weight = 0.05529208;
  double late_weight = 0.12633207;
  double critical_weight = 0.34337678;
  unsigned budget = 9;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
