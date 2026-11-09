// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01256898;
  double density_weight = 0.01926335;
  double prefix_weight = 0.31470307;
  double neighborhood_weight = 0.23566905;
  double late_weight = 0.25009125;
  double critical_weight = 0.43650116;
  unsigned budget = 28;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
