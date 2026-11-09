// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56072162;
  double density_weight = 0.58213283;
  double prefix_weight = 0.46241017;
  double neighborhood_weight = 0.37632943;
  double late_weight = 0.01637424;
  double critical_weight = 0.27556447;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
