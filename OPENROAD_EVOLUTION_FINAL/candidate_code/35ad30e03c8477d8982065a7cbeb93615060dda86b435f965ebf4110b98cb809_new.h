// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55062086;
  double density_weight = 0.20828925;
  double prefix_weight = 0.32344234;
  double neighborhood_weight = 0.00036847;
  double late_weight = 0.03871076;
  double critical_weight = 0.11846557;
  unsigned budget = 29;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
