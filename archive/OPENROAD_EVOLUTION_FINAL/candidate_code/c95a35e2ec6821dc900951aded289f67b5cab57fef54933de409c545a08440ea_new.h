// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45186686;
  double density_weight = 0.04093001;
  double prefix_weight = 0.15510906;
  double neighborhood_weight = 0.16099637;
  double late_weight = 0.00387619;
  double critical_weight = 0.29163309;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
