// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00542641;
  double density_weight = 0.50031167;
  double prefix_weight = 0.21253465;
  double neighborhood_weight = 0.03064415;
  double late_weight = 0.17423044;
  double critical_weight = 0.16177987;
  unsigned budget = 22;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
