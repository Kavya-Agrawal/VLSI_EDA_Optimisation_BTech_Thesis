// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16821373;
  double density_weight = 0.23648464;
  double prefix_weight = 0.09351412;
  double neighborhood_weight = 0.13115183;
  double late_weight = 0.14760606;
  double critical_weight = 0.24027046;
  unsigned budget = 18;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
