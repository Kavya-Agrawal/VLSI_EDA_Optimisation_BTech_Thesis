// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20934498;
  double density_weight = 0.28072705;
  double prefix_weight = 0.29962455;
  double neighborhood_weight = 0.25641339;
  double late_weight = 0.10411154;
  double critical_weight = 0.48537724;
  unsigned budget = 8;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
