// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66669775;
  double density_weight = 0.38538546;
  double prefix_weight = 0.44318878;
  double neighborhood_weight = 0.35174006;
  double late_weight = 0.10176252;
  double critical_weight = 0.27336053;
  unsigned budget = 28;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
