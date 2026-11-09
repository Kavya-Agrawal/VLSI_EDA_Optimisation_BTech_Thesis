// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51339100;
  double density_weight = 0.04126284;
  double prefix_weight = 0.25461291;
  double neighborhood_weight = 0.27820059;
  double late_weight = 0.17186398;
  double critical_weight = 0.40422518;
  unsigned budget = 22;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
