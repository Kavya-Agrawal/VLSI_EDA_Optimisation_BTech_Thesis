// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41416425;
  double density_weight = 0.54208446;
  double prefix_weight = 0.07610172;
  double neighborhood_weight = 0.25179364;
  double late_weight = 0.09323674;
  double critical_weight = 0.12395235;
  unsigned budget = 9;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
