// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55500637;
  double density_weight = 0.48482605;
  double prefix_weight = 0.06439307;
  double neighborhood_weight = 0.21028667;
  double late_weight = 0.06340778;
  double critical_weight = 0.26898595;
  unsigned budget = 39;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
