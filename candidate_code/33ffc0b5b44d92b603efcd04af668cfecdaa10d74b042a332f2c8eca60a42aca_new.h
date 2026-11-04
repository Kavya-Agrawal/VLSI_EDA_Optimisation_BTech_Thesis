// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88934206;
  double density_weight = 0.39591843;
  double prefix_weight = 0.29985128;
  double neighborhood_weight = 0.16058406;
  double late_weight = 0.01951621;
  double critical_weight = 0.09428536;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
