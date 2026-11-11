// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79588589;
  double density_weight = 0.44738434;
  double prefix_weight = 0.36645930;
  double neighborhood_weight = 0.39274421;
  double late_weight = 0.24494377;
  double critical_weight = 0.26965362;
  unsigned budget = 29;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
