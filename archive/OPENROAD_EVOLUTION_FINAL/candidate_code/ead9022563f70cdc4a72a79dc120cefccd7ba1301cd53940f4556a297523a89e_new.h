// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27919132;
  double density_weight = 0.33186874;
  double prefix_weight = 0.09049544;
  double neighborhood_weight = 0.09622085;
  double late_weight = 0.10478708;
  double critical_weight = 0.45410774;
  unsigned budget = 22;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
