// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88378542;
  double density_weight = 0.52590527;
  double prefix_weight = 0.16559378;
  double neighborhood_weight = 0.12183378;
  double late_weight = 0.06934917;
  double critical_weight = 0.38023188;
  unsigned budget = 23;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
