// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58297408;
  double density_weight = 0.15429427;
  double prefix_weight = 0.04775108;
  double neighborhood_weight = 0.21094735;
  double late_weight = 0.01375092;
  double critical_weight = 0.30271057;
  unsigned budget = 23;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
