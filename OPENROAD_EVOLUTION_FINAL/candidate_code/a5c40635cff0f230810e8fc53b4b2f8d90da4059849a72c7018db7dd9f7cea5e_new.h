// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51595279;
  double density_weight = 0.41026875;
  double prefix_weight = 0.47370860;
  double neighborhood_weight = 0.25463545;
  double late_weight = 0.29500587;
  double critical_weight = 0.41278869;
  unsigned budget = 16;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
