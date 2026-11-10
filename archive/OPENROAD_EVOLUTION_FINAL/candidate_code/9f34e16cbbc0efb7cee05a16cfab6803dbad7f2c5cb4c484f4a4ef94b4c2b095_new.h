// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42544429;
  double density_weight = 0.34670231;
  double prefix_weight = 0.35544799;
  double neighborhood_weight = 0.23032782;
  double late_weight = 0.20911055;
  double critical_weight = 0.31510957;
  unsigned budget = 40;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
