// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41090459;
  double density_weight = 0.35228856;
  double prefix_weight = 0.08969201;
  double neighborhood_weight = 0.01314407;
  double late_weight = 0.02689540;
  double critical_weight = 0.21028144;
  unsigned budget = 23;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
