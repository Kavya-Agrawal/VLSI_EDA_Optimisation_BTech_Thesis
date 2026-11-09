// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49304673;
  double density_weight = 0.40788999;
  double prefix_weight = 0.23999202;
  double neighborhood_weight = 0.23882902;
  double late_weight = 0.19839972;
  double critical_weight = 0.08661861;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
