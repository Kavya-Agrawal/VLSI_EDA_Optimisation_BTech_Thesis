// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17545658;
  double density_weight = 0.22641684;
  double prefix_weight = 0.15301931;
  double neighborhood_weight = 0.09993783;
  double late_weight = 0.04093072;
  double critical_weight = 0.03336752;
  unsigned budget = 18;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
