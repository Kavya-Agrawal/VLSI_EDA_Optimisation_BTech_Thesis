// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40670167;
  double density_weight = 0.23624672;
  double prefix_weight = 0.26895463;
  double neighborhood_weight = 0.20456395;
  double late_weight = 0.16122471;
  double critical_weight = 0.34390817;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
