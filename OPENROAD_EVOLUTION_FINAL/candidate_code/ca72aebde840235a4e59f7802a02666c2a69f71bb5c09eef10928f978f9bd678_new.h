// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61845347;
  double density_weight = 0.48852545;
  double prefix_weight = 0.04823735;
  double neighborhood_weight = 0.30673578;
  double late_weight = 0.15870809;
  double critical_weight = 0.43413980;
  unsigned budget = 12;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
