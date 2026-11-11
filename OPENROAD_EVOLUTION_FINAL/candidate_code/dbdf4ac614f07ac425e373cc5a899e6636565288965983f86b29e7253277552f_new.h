// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31067666;
  double density_weight = 0.43179751;
  double prefix_weight = 0.14360626;
  double neighborhood_weight = 0.21121702;
  double late_weight = 0.20994162;
  double critical_weight = 0.00939466;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
