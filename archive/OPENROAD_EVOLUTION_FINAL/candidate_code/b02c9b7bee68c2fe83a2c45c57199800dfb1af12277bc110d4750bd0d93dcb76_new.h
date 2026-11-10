// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64442841;
  double density_weight = 0.49420620;
  double prefix_weight = 0.49653911;
  double neighborhood_weight = 0.34877288;
  double late_weight = 0.19731644;
  double critical_weight = 0.43395458;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
