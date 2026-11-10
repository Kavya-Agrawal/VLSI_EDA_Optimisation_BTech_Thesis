// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04104361;
  double density_weight = 0.37651256;
  double prefix_weight = 0.11787518;
  double neighborhood_weight = 0.05890947;
  double late_weight = 0.26215826;
  double critical_weight = 0.05561368;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
