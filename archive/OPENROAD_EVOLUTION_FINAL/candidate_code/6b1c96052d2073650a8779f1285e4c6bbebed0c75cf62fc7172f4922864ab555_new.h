// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65466989;
  double density_weight = 0.28589792;
  double prefix_weight = 0.36155582;
  double neighborhood_weight = 0.07062752;
  double late_weight = 0.21930795;
  double critical_weight = 0.16312324;
  unsigned budget = 34;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
