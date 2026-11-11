// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64950717;
  double density_weight = 0.31506451;
  double prefix_weight = 0.49586301;
  double neighborhood_weight = 0.11362901;
  double late_weight = 0.25598869;
  double critical_weight = 0.33254959;
  unsigned budget = 15;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
