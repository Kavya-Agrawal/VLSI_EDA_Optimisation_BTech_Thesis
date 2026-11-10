// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53580450;
  double density_weight = 0.39346867;
  double prefix_weight = 0.37890601;
  double neighborhood_weight = 0.13637168;
  double late_weight = 0.23460632;
  double critical_weight = 0.04869347;
  unsigned budget = 17;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
