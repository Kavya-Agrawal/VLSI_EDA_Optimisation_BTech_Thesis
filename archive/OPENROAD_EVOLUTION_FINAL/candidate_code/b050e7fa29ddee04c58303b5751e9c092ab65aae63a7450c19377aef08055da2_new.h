// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04737283;
  double density_weight = 0.27525570;
  double prefix_weight = 0.11657979;
  double neighborhood_weight = 0.28668181;
  double late_weight = 0.04682591;
  double critical_weight = 0.29575523;
  unsigned budget = 17;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
