// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79120785;
  double density_weight = 0.30379675;
  double prefix_weight = 0.27221434;
  double neighborhood_weight = 0.10795145;
  double late_weight = 0.05474196;
  double critical_weight = 0.33481957;
  unsigned budget = 37;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
