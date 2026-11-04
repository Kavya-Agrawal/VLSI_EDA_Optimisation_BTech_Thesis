// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62989268;
  double density_weight = 0.48761591;
  double prefix_weight = 0.43626932;
  double neighborhood_weight = 0.24837042;
  double late_weight = 0.12759930;
  double critical_weight = 0.31888004;
  unsigned budget = 30;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
