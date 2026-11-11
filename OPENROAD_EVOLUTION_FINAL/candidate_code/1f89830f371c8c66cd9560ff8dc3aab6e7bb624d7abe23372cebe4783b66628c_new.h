// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64286356;
  double density_weight = 0.17989980;
  double prefix_weight = 0.45764950;
  double neighborhood_weight = 0.20918137;
  double late_weight = 0.25047797;
  double critical_weight = 0.45156088;
  unsigned budget = 19;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
