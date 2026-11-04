// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46575736;
  double density_weight = 0.20247532;
  double prefix_weight = 0.30819558;
  double neighborhood_weight = 0.33577232;
  double late_weight = 0.19430772;
  double critical_weight = 0.31980080;
  unsigned budget = 7;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
