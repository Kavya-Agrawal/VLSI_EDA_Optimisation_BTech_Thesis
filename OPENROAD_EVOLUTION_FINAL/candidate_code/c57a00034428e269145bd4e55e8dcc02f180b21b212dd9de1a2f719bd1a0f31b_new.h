// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56992852;
  double density_weight = 0.27980213;
  double prefix_weight = 0.41088720;
  double neighborhood_weight = 0.12817473;
  double late_weight = 0.17677259;
  double critical_weight = 0.30489701;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
