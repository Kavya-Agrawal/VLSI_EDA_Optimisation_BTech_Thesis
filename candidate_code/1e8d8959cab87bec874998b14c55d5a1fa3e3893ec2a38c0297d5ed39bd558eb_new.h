// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91494514;
  double density_weight = 0.22897281;
  double prefix_weight = 0.01360500;
  double neighborhood_weight = 0.35510862;
  double late_weight = 0.09748790;
  double critical_weight = 0.06261959;
  unsigned budget = 34;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
