// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33889021;
  double density_weight = 0.19340917;
  double prefix_weight = 0.21738109;
  double neighborhood_weight = 0.02822436;
  double late_weight = 0.14179584;
  double critical_weight = 0.27355143;
  unsigned budget = 36;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
