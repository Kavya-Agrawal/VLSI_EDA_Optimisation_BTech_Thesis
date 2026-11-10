// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22362053;
  double density_weight = 0.54867608;
  double prefix_weight = 0.23627889;
  double neighborhood_weight = 0.13273389;
  double late_weight = 0.14906542;
  double critical_weight = 0.17386852;
  unsigned budget = 29;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
