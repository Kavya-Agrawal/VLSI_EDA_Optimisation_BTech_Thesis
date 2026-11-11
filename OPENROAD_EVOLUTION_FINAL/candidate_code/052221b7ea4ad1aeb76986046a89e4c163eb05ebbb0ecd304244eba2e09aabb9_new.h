// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36829365;
  double density_weight = 0.29760442;
  double prefix_weight = 0.14295907;
  double neighborhood_weight = 0.28754107;
  double late_weight = 0.04705708;
  double critical_weight = 0.28546138;
  unsigned budget = 6;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
