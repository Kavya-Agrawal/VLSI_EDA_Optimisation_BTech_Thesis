// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62369912;
  double density_weight = 0.42934498;
  double prefix_weight = 0.37638788;
  double neighborhood_weight = 0.31668190;
  double late_weight = 0.00995718;
  double critical_weight = 0.10388765;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
