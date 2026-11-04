// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77198833;
  double density_weight = 0.15378368;
  double prefix_weight = 0.42808828;
  double neighborhood_weight = 0.27031464;
  double late_weight = 0.27883157;
  double critical_weight = 0.12282986;
  unsigned budget = 4;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
