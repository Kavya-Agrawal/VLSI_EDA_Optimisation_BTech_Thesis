// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56769295;
  double density_weight = 0.09193441;
  double prefix_weight = 0.20867388;
  double neighborhood_weight = 0.19141880;
  double late_weight = 0.26575320;
  double critical_weight = 0.22485793;
  unsigned budget = 36;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
