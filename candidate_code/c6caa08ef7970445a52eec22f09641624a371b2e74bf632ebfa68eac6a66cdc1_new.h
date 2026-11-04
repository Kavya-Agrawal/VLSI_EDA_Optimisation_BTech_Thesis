// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12853455;
  double density_weight = 0.09451253;
  double prefix_weight = 0.35745962;
  double neighborhood_weight = 0.31585829;
  double late_weight = 0.05147847;
  double critical_weight = 0.22413054;
  unsigned budget = 40;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
