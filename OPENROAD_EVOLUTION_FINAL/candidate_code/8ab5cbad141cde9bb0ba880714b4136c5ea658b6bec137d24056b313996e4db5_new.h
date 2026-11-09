// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00722361;
  double density_weight = 0.41877089;
  double prefix_weight = 0.34527794;
  double neighborhood_weight = 0.18304877;
  double late_weight = 0.29609910;
  double critical_weight = 0.22159525;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
