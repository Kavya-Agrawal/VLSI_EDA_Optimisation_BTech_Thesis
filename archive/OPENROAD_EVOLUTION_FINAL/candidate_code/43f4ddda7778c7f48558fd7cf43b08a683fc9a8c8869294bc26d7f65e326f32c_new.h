// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08547678;
  double density_weight = 0.20656088;
  double prefix_weight = 0.26061352;
  double neighborhood_weight = 0.02419418;
  double late_weight = 0.18073415;
  double critical_weight = 0.42570787;
  unsigned budget = 13;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
