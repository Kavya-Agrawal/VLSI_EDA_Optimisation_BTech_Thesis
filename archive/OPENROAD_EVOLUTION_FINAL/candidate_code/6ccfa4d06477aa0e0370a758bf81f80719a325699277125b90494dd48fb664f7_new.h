// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00570516;
  double density_weight = 0.07320015;
  double prefix_weight = 0.15912383;
  double neighborhood_weight = 0.24261737;
  double late_weight = 0.17596240;
  double critical_weight = 0.34746960;
  unsigned budget = 4;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
