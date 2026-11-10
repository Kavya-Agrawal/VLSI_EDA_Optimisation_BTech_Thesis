// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07862494;
  double density_weight = 0.28060300;
  double prefix_weight = 0.43164260;
  double neighborhood_weight = 0.33197427;
  double late_weight = 0.19493207;
  double critical_weight = 0.09639223;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
