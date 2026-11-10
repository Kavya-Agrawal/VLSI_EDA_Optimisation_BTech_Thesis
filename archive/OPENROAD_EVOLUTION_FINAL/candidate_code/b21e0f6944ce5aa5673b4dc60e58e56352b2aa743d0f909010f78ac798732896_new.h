// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97967286;
  double density_weight = 0.45730427;
  double prefix_weight = 0.26628963;
  double neighborhood_weight = 0.23327284;
  double late_weight = 0.08295989;
  double critical_weight = 0.43125203;
  unsigned budget = 22;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
