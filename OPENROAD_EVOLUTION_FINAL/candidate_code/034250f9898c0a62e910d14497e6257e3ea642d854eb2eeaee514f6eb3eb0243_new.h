// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53567303;
  double density_weight = 0.05117231;
  double prefix_weight = 0.12446511;
  double neighborhood_weight = 0.34201732;
  double late_weight = 0.05847712;
  double critical_weight = 0.35897823;
  unsigned budget = 6;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
