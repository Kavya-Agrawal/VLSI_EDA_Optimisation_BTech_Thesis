// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29748291;
  double density_weight = 0.26664510;
  double prefix_weight = 0.40224199;
  double neighborhood_weight = 0.14124410;
  double late_weight = 0.07270637;
  double critical_weight = 0.20080288;
  unsigned budget = 8;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
