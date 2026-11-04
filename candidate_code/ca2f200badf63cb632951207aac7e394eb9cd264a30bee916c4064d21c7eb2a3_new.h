// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83523833;
  double density_weight = 0.39485976;
  double prefix_weight = 0.48995833;
  double neighborhood_weight = 0.20793098;
  double late_weight = 0.04240060;
  double critical_weight = 0.21420939;
  unsigned budget = 15;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
