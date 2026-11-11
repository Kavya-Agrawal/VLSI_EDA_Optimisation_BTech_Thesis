// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74174186;
  double density_weight = 0.10094723;
  double prefix_weight = 0.41339022;
  double neighborhood_weight = 0.00717075;
  double late_weight = 0.05244644;
  double critical_weight = 0.07382444;
  unsigned budget = 10;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
