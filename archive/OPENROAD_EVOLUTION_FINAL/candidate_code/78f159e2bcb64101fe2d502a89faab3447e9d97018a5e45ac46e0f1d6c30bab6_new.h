// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56932601;
  double density_weight = 0.36276188;
  double prefix_weight = 0.01159842;
  double neighborhood_weight = 0.22579627;
  double late_weight = 0.09223959;
  double critical_weight = 0.35188148;
  unsigned budget = 31;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
