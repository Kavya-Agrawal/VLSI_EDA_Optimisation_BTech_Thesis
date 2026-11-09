// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22396675;
  double density_weight = 0.53909328;
  double prefix_weight = 0.05225784;
  double neighborhood_weight = 0.04386818;
  double late_weight = 0.04365940;
  double critical_weight = 0.31561929;
  unsigned budget = 27;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
