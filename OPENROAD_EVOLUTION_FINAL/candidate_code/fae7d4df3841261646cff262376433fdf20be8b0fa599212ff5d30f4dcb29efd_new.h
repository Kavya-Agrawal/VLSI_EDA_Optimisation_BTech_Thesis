// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59535744;
  double density_weight = 0.57442885;
  double prefix_weight = 0.18103339;
  double neighborhood_weight = 0.37157944;
  double late_weight = 0.04114916;
  double critical_weight = 0.04164063;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
