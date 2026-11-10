// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65349987;
  double density_weight = 0.40824778;
  double prefix_weight = 0.47638060;
  double neighborhood_weight = 0.36820205;
  double late_weight = 0.01447292;
  double critical_weight = 0.11244897;
  unsigned budget = 7;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
