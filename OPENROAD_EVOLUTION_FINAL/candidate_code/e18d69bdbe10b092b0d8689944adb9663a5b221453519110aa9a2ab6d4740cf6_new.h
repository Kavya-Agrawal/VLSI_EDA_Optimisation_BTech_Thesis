// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40322922;
  double density_weight = 0.41599301;
  double prefix_weight = 0.32949605;
  double neighborhood_weight = 0.14161598;
  double late_weight = 0.04778634;
  double critical_weight = 0.48917070;
  unsigned budget = 5;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
