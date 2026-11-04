// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84159891;
  double density_weight = 0.56121472;
  double prefix_weight = 0.47206815;
  double neighborhood_weight = 0.11421053;
  double late_weight = 0.15194460;
  double critical_weight = 0.22347159;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
