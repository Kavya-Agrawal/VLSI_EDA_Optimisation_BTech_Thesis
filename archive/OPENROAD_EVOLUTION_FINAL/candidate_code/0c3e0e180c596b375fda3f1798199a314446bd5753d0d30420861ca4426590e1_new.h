// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33451280;
  double density_weight = 0.44502347;
  double prefix_weight = 0.12936673;
  double neighborhood_weight = 0.36371450;
  double late_weight = 0.07629306;
  double critical_weight = 0.07576420;
  unsigned budget = 26;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
