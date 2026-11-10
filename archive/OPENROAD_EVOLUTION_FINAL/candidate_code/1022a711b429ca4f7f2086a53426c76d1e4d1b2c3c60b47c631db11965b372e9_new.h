// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51451317;
  double density_weight = 0.14252542;
  double prefix_weight = 0.46685586;
  double neighborhood_weight = 0.12379848;
  double late_weight = 0.06130594;
  double critical_weight = 0.17201578;
  unsigned budget = 17;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
