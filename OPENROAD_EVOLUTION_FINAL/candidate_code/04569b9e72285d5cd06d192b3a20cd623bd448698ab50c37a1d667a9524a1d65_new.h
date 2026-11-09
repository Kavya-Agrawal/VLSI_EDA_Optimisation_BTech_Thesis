// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58231992;
  double density_weight = 0.04842729;
  double prefix_weight = 0.30346499;
  double neighborhood_weight = 0.23533269;
  double late_weight = 0.04682223;
  double critical_weight = 0.46318125;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
