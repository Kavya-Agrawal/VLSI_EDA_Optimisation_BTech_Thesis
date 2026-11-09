// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56978456;
  double density_weight = 0.32148756;
  double prefix_weight = 0.13595782;
  double neighborhood_weight = 0.23025822;
  double late_weight = 0.06672429;
  double critical_weight = 0.42171535;
  unsigned budget = 6;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
