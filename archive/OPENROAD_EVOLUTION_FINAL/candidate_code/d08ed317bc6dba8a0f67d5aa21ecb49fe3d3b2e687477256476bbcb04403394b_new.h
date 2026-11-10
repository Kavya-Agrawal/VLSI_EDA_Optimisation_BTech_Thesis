// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91167825;
  double density_weight = 0.50690160;
  double prefix_weight = 0.04890601;
  double neighborhood_weight = 0.13888174;
  double late_weight = 0.14467566;
  double critical_weight = 0.04658432;
  unsigned budget = 27;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
