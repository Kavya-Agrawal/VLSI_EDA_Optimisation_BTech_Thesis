// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02110274;
  double density_weight = 0.31767192;
  double prefix_weight = 0.04518325;
  double neighborhood_weight = 0.26679726;
  double late_weight = 0.18345698;
  double critical_weight = 0.19939600;
  unsigned budget = 6;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
