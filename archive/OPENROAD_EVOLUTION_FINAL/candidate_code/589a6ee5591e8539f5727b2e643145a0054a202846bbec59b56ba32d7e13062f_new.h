// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27042256;
  double density_weight = 0.33799990;
  double prefix_weight = 0.30607319;
  double neighborhood_weight = 0.17096372;
  double late_weight = 0.19214586;
  double critical_weight = 0.29682841;
  unsigned budget = 32;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
