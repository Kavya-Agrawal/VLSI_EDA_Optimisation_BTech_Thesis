// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03923055;
  double density_weight = 0.44537914;
  double prefix_weight = 0.26758747;
  double neighborhood_weight = 0.37039091;
  double late_weight = 0.10198945;
  double critical_weight = 0.17765204;
  unsigned budget = 37;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
