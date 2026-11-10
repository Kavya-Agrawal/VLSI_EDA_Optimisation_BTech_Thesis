// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71098678;
  double density_weight = 0.30725891;
  double prefix_weight = 0.39406655;
  double neighborhood_weight = 0.24649151;
  double late_weight = 0.11724099;
  double critical_weight = 0.49615036;
  unsigned budget = 6;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
