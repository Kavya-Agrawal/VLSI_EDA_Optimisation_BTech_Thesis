// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91257089;
  double density_weight = 0.04909702;
  double prefix_weight = 0.02199088;
  double neighborhood_weight = 0.23780344;
  double late_weight = 0.22089718;
  double critical_weight = 0.37480836;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
