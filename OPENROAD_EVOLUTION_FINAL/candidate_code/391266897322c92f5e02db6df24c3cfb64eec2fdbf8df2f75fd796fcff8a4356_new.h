// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67272276;
  double density_weight = 0.55701259;
  double prefix_weight = 0.49126737;
  double neighborhood_weight = 0.18497235;
  double late_weight = 0.10089052;
  double critical_weight = 0.49680399;
  unsigned budget = 12;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
