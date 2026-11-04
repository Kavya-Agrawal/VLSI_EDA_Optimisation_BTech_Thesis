// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69954696;
  double density_weight = 0.33955055;
  double prefix_weight = 0.34167673;
  double neighborhood_weight = 0.08995104;
  double late_weight = 0.29042241;
  double critical_weight = 0.03871265;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
