// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10957551;
  double density_weight = 0.32590784;
  double prefix_weight = 0.19546291;
  double neighborhood_weight = 0.23126575;
  double late_weight = 0.14633595;
  double critical_weight = 0.32749558;
  unsigned budget = 34;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
