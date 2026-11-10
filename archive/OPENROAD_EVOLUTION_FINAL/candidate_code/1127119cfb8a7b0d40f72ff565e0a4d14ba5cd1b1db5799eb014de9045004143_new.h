// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61495176;
  double density_weight = 0.11233264;
  double prefix_weight = 0.12097550;
  double neighborhood_weight = 0.03710621;
  double late_weight = 0.05933869;
  double critical_weight = 0.01086108;
  unsigned budget = 28;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
