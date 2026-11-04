// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88074750;
  double density_weight = 0.16291822;
  double prefix_weight = 0.43252549;
  double neighborhood_weight = 0.28709295;
  double late_weight = 0.06263878;
  double critical_weight = 0.01838908;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
