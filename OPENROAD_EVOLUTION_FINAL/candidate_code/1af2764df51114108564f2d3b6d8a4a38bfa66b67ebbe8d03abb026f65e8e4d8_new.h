// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56440071;
  double density_weight = 0.39642298;
  double prefix_weight = 0.11147180;
  double neighborhood_weight = 0.25766907;
  double late_weight = 0.05279347;
  double critical_weight = 0.11365919;
  unsigned budget = 31;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
