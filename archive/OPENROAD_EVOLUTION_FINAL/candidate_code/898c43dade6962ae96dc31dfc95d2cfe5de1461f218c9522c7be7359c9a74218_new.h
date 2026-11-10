// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46695984;
  double density_weight = 0.55942269;
  double prefix_weight = 0.14855258;
  double neighborhood_weight = 0.33192150;
  double late_weight = 0.08705277;
  double critical_weight = 0.03007183;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
