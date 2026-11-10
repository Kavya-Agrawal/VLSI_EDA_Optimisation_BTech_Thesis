// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24145672;
  double density_weight = 0.07921609;
  double prefix_weight = 0.02239945;
  double neighborhood_weight = 0.22910104;
  double late_weight = 0.15265623;
  double critical_weight = 0.33632377;
  unsigned budget = 7;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
