// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41020858;
  double density_weight = 0.35084695;
  double prefix_weight = 0.07602288;
  double neighborhood_weight = 0.01080101;
  double late_weight = 0.03225801;
  double critical_weight = 0.12330051;
  unsigned budget = 4;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
