// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27711528;
  double density_weight = 0.20982960;
  double prefix_weight = 0.03572870;
  double neighborhood_weight = 0.13441628;
  double late_weight = 0.26418322;
  double critical_weight = 0.45762372;
  unsigned budget = 18;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
