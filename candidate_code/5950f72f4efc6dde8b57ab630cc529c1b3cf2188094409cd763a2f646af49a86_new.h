// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53118868;
  double density_weight = 0.40547888;
  double prefix_weight = 0.40746259;
  double neighborhood_weight = 0.04303455;
  double late_weight = 0.24525533;
  double critical_weight = 0.36813790;
  unsigned budget = 28;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
