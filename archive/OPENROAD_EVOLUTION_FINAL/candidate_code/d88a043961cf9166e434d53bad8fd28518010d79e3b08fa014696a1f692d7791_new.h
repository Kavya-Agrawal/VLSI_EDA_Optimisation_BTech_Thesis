// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35577916;
  double density_weight = 0.00540646;
  double prefix_weight = 0.32918988;
  double neighborhood_weight = 0.22937107;
  double late_weight = 0.05231620;
  double critical_weight = 0.30145557;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
