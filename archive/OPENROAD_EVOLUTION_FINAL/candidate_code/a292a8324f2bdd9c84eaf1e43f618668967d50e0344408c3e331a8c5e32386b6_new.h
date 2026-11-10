// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03257335;
  double density_weight = 0.55912938;
  double prefix_weight = 0.45916256;
  double neighborhood_weight = 0.06378590;
  double late_weight = 0.16501984;
  double critical_weight = 0.04002863;
  unsigned budget = 30;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
