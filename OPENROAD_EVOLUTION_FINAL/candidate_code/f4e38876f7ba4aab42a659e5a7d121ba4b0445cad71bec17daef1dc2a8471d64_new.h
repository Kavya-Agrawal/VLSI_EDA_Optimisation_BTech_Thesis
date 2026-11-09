// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19674965;
  double density_weight = 0.45077980;
  double prefix_weight = 0.41376148;
  double neighborhood_weight = 0.21770097;
  double late_weight = 0.29200466;
  double critical_weight = 0.10620606;
  unsigned budget = 8;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
