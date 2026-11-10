// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41720637;
  double density_weight = 0.06871152;
  double prefix_weight = 0.41417723;
  double neighborhood_weight = 0.37698833;
  double late_weight = 0.27509404;
  double critical_weight = 0.32876010;
  unsigned budget = 10;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
