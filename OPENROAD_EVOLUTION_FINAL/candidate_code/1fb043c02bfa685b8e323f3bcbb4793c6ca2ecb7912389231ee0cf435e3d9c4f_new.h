// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90988626;
  double density_weight = 0.32358621;
  double prefix_weight = 0.35258159;
  double neighborhood_weight = 0.03633725;
  double late_weight = 0.04599028;
  double critical_weight = 0.49389232;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
