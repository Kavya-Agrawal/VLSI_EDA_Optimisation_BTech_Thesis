// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55808623;
  double density_weight = 0.22851179;
  double prefix_weight = 0.16451709;
  double neighborhood_weight = 0.12988957;
  double late_weight = 0.17023859;
  double critical_weight = 0.19116768;
  unsigned budget = 35;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
