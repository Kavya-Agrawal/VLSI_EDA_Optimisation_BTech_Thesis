// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52776463;
  double density_weight = 0.53824640;
  double prefix_weight = 0.37852305;
  double neighborhood_weight = 0.28497334;
  double late_weight = 0.09459855;
  double critical_weight = 0.24901188;
  unsigned budget = 28;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
