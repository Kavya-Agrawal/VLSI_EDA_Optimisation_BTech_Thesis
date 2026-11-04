// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63493176;
  double density_weight = 0.58586131;
  double prefix_weight = 0.17317244;
  double neighborhood_weight = 0.32316872;
  double late_weight = 0.29760268;
  double critical_weight = 0.27116694;
  unsigned budget = 9;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
