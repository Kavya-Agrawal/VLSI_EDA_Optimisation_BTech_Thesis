// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44554885;
  double density_weight = 0.54289625;
  double prefix_weight = 0.39736239;
  double neighborhood_weight = 0.27667623;
  double late_weight = 0.28152270;
  double critical_weight = 0.16745733;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
