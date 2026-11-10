// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54507392;
  double density_weight = 0.20488376;
  double prefix_weight = 0.12706439;
  double neighborhood_weight = 0.14021847;
  double late_weight = 0.20600524;
  double critical_weight = 0.48116621;
  unsigned budget = 12;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
