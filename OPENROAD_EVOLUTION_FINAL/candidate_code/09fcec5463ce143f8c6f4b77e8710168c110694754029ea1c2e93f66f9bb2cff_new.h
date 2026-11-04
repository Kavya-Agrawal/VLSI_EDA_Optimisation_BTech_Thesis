// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14065436;
  double density_weight = 0.11643726;
  double prefix_weight = 0.32541637;
  double neighborhood_weight = 0.03030914;
  double late_weight = 0.13897698;
  double critical_weight = 0.32889441;
  unsigned budget = 23;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
