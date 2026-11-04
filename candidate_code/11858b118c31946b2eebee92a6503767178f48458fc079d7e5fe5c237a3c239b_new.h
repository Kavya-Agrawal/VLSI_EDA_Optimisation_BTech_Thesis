// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78926747;
  double density_weight = 0.03501247;
  double prefix_weight = 0.31053090;
  double neighborhood_weight = 0.04607898;
  double late_weight = 0.22213421;
  double critical_weight = 0.49655801;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
