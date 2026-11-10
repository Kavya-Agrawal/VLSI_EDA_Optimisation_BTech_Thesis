// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34819140;
  double density_weight = 0.13620285;
  double prefix_weight = 0.12052468;
  double neighborhood_weight = 0.10988270;
  double late_weight = 0.01443599;
  double critical_weight = 0.34107030;
  unsigned budget = 37;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
