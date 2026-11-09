// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13068592;
  double density_weight = 0.13151568;
  double prefix_weight = 0.14238096;
  double neighborhood_weight = 0.05454182;
  double late_weight = 0.16316081;
  double critical_weight = 0.34014343;
  unsigned budget = 10;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
