// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53324169;
  double density_weight = 0.41643131;
  double prefix_weight = 0.46470748;
  double neighborhood_weight = 0.24735275;
  double late_weight = 0.16621193;
  double critical_weight = 0.27354962;
  unsigned budget = 38;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
