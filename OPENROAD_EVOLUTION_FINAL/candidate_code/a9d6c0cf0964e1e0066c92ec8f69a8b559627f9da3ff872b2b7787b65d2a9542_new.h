// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42591524;
  double density_weight = 0.03688222;
  double prefix_weight = 0.44196347;
  double neighborhood_weight = 0.18801730;
  double late_weight = 0.14276189;
  double critical_weight = 0.19332316;
  unsigned budget = 7;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
