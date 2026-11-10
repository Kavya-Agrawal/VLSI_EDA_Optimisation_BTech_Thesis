// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25253051;
  double density_weight = 0.57783313;
  double prefix_weight = 0.09430334;
  double neighborhood_weight = 0.32476933;
  double late_weight = 0.29985546;
  double critical_weight = 0.18895734;
  unsigned budget = 35;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
