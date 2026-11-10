// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52537309;
  double density_weight = 0.33783336;
  double prefix_weight = 0.06712487;
  double neighborhood_weight = 0.05406753;
  double late_weight = 0.21036622;
  double critical_weight = 0.08795861;
  unsigned budget = 5;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
